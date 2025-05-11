#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/wait.h>

#define DEVICE_NAME "waitqueue_device"

static dev_t dev_number;
static struct cdev etx_cdev;
static struct class *dev_class;
static struct task_struct *wait_thread;
static wait_queue_head_t wait_queue_etx;
static int wait_queue_flag = 0;

static int wait_function(void *unused)
{
    while (!kthread_should_stop()) {
        pr_info("Waiting for event...\n");
        wait_event_interruptible(wait_queue_etx, wait_queue_flag != 0);
        if (wait_queue_flag == 2) {
            pr_info("Event received from exit function\n");
            break;
        }
        pr_info("Event received from read function\n");
        wait_queue_flag = 0;
    }
    return 0;
}

static int etx_open(struct inode *inode, struct file *file)
{
    pr_info("Device file opened\n");
    return 0;
}

static int etx_release(struct inode *inode, struct file *file)
{
    pr_info("Device file closed\n");
    return 0;
}

static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    pr_info("Read function\n");
    wait_queue_flag = 1;
    wake_up_interruptible(&wait_queue_etx);
    return 0;
}

static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    pr_info("Write function\n");
    return len;
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = etx_read,
    .write = etx_write,
    .open = etx_open,
    .release = etx_release,
};

static int __init etx_driver_init(void)
{
    if ((alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME)) < 0) {
        pr_err("Cannot allocate major number\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d\n", MAJOR(dev_number), MINOR(dev_number));

    cdev_init(&etx_cdev, &fops);

    if ((cdev_add(&etx_cdev, dev_number, 1)) < 0) {
        pr_err("Cannot add the device to the system\n");
        goto r_class;
    }

    if (IS_ERR(dev_class = class_create(THIS_MODULE, "etx_class"))) {
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }

    if (IS_ERR(device_create(dev_class, NULL, dev_number, NULL, DEVICE_NAME))) {
        pr_err("Cannot create the Device\n");
        goto r_device;
    }

    init_waitqueue_head(&wait_queue_etx);

    wait_thread = kthread_create(wait_function, NULL, "WaitThread");
    if (wait_thread) {
        pr_info("Thread created successfully\n");
        wake_up_process(wait_thread);
    } else {
        pr_err("Thread creation failed\n");
        goto r_device;
    }

    pr_info("Device Driver Inserted Successfully\n");
    return 0;

r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev_number, 1);
    return -1;
}

static void __exit etx_driver_exit(void)
{
    wait_queue_flag = 2;
    wake_up_interruptible(&wait_queue_etx);
    kthread_stop(wait_thread);
    device_destroy(dev_class, dev_number);
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev_number, 1);
    pr_info("Device Driver Removed Successfully\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("A simple device driver demonstrating waitqueues");
MODULE_VERSION("1.0");

