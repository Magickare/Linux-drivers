
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_cdev"
#define CLASS_NAME  "my_class"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Simple Character Device with cdev");
MODULE_VERSION("1.0");

static int major;
static char kernel_buffer[256] = "Hello from Gowtham!\n";
static struct class *dev_class;
static struct cdev my_cdev;
dev_t dev_num;

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    int ret = copy_to_user(buf, kernel_buffer, strlen(kernel_buffer));
    if (ret != 0)
        printk(KERN_ERR "Failed to copy data to user\n");
    return strlen(kernel_buffer);
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    int ret = copy_from_user(kernel_buffer, buf, len);
    kernel_buffer[len] = '\0';
    printk(KERN_INFO "Data written: %s\n", kernel_buffer);
    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int __init my_driver_init(void) {
    if ((alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME)) < 0) {
        printk(KERN_ERR "Failed to allocate char device region\n");
        return -1;
    }

    major = MAJOR(dev_num);
    printk(KERN_INFO "Major number: %d\n", major);

    cdev_init(&my_cdev, &fops);
    if ((cdev_add(&my_cdev, dev_num, 1)) < 0) {
        printk(KERN_ERR "Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    dev_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(dev_class)) {
        printk(KERN_ERR "Failed to create device class\n");
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(dev_class);
    }

    if (IS_ERR(device_create(dev_class, NULL, dev_num, NULL, DEVICE_NAME))) {
        printk(KERN_ERR "Failed to create device\n");
        class_destroy(dev_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    printk(KERN_INFO "Driver loaded successfully\n");
    return 0;
}

static void __exit my_driver_exit(void) {
    device_destroy(dev_class, dev_num);
    class_destroy(dev_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Driver unloaded\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

