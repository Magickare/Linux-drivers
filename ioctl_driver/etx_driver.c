#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int32_t value = 0;
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

static int etx_open(struct inode *inode, struct file *file) {
    pr_info("Device File Opened\n");
    return 0;
}

static int etx_release(struct inode *inode, struct file *file) {
    pr_info("Device File Closed\n");
    return 0;
}

static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off) {
    pr_info("Read Function\n");
    return 0;
}

static ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t *off) {
    pr_info("Write Function\n");
    return len;
}

static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case WR_VALUE:
            copy_from_user(&value, (int32_t*) arg, sizeof(value));
            pr_info("Value written: %d\n", value);
            break;
        case RD_VALUE:
            copy_to_user((int32_t*) arg, &value, sizeof(value));
            break;
    }
    return 0;
}

static struct file_operations fops = {
    .owner          = THIS_MODULE,
    .read           = etx_read,
    .write          = etx_write,
    .open           = etx_open,
    .unlocked_ioctl = etx_ioctl,
    .release        = etx_release,
};

static int __init etx_driver_init(void) {
    alloc_chrdev_region(&dev, 0, 1, "etx_Dev");
    cdev_init(&etx_cdev, &fops);
    cdev_add(&etx_cdev, dev, 1);
    dev_class = class_create(THIS_MODULE, "etx_class");
    device_create(dev_class, NULL, dev, NULL, "etx_device");
    pr_info("Driver Inserted\n");
    return 0;
}

static void __exit etx_driver_exit(void) {
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("Driver Removed\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");

