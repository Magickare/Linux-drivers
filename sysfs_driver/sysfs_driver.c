#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>

static struct kobject *kobj_ref;
static int etx_value;

/* Sysfs show function */
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    printk(KERN_INFO "Sysfs - Read\n");
    return sprintf(buf, "%d", etx_value);
}

/* Sysfs store function */
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    printk(KERN_INFO "Sysfs - Write\n");
    sscanf(buf, "%d", &etx_value);
    return count;
}

/* Create attribute */
struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);

/* Init function */
static int __init my_sysfs_init(void)
{
    /* Creating a directory under /sys/kernel/ */
    kobj_ref = kobject_create_and_add("etx_sysfs", kernel_kobj);

    /* Creating a file under the above directory */
    if (sysfs_create_file(kobj_ref, &etx_attr.attr)) {
        printk(KERN_ERR "Cannot create sysfs file\n");
        kobject_put(kobj_ref);
        return -ENOMEM;
    }

    printk(KERN_INFO "Sysfs driver inserted\n");
    return 0;
}

/* Exit function */
static void __exit my_sysfs_exit(void)
{
    sysfs_remove_file(kobj_ref, &etx_attr.attr);
    kobject_put(kobj_ref);
    printk(KERN_INFO "Sysfs driver removed\n");
}

module_init(my_sysfs_init);
module_exit(my_sysfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbetronicX");
MODULE_DESCRIPTION("Linux device driver - Sysfs example");

