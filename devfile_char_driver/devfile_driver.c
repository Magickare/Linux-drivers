#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_device"

dev_t dev;
struct cdev my_cdev;
char kernel_buffer[100];

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off) {
    copy_to_user(buf, kernel_buffer, strlen(kernel_buffer));
    printk(KERN_INFO "Data read: %s\n", kernel_buffer);
    return strlen(kernel_buffer);
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off) {
    copy_from_user(kernel_buffer, buf, len);
    kernel_buffer[len] = '\0';
    printk(KERN_INFO "Data written: %s\n", kernel_buffer);
    return len;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int __init my_driver_init(void) {
    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    cdev_init(&my_cdev, &fops);
    cdev_add(&my_cdev, dev, 1);
    printk(KERN_INFO "Driver loaded: Major = %d, Minor = %d\n", MAJOR(dev), MINOR(dev));
    return 0;
}

static void __exit my_driver_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Driver unloaded\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gowtham");
MODULE_DESCRIPTION("Simple char driver with device file");

