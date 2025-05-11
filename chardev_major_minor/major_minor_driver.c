#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DRIVER_NAME "siddhu_device"
dev_t dev_num;


static struct cdev my_cdev;
dev_t dev_num;

static int __init my_driver_init(void) {
    if (alloc_chrdev_region(&dev_num, 0, 1, DRIVER_NAME) < 0) {
        pr_err("Failed to allocate char device region\n");
        return -1;
    }

    cdev_init(&my_cdev, NULL);
    cdev_add(&my_cdev, dev_num, 1);

    pr_info("Driver inserted: Major = %d, Minor = %d\n", MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

static void __exit my_driver_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("Driver removed\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Simple Char Device with Major and Minor Numbers");

