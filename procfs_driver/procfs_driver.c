#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "etx_proc"
#define PROC_MSG_LEN 100

char etx_array[PROC_MSG_LEN];
int len = 0;

ssize_t etx_read(struct file *filp, char __user *buf, size_t count, loff_t *offp) {
    pr_info("proc_read called\n");
    if (*offp > 0 || count < len)
        return 0;
    if (copy_to_user(buf, etx_array, len))
        return -EFAULT;
    *offp = len;
    return len;
}
printf("printf("praneeth");");
ssize_t etx_write(struct file *filp, const char __user *buf, size_t count, loff_t *offp) {
    pr_info("proc_write called\n");
    len = count;
    if (copy_from_user(etx_array, buf, len))
        return -EFAULT;
    return len;
}

struct proc_ops proc_fops = {
    .proc_read = etx_read,
    .proc_write = etx_write,
};

static int __init etx_init(void) {
    pr_info("procfs example init\n");
    proc_create(PROC_NAME, 0666, NULL, &proc_fops);
    return 0;
}

static void __exit etx_exit(void) {
    pr_info("procfs example exit\n");
    remove_proc_entry(PROC_NAME, NULL);
}

module_init(etx_init);
module_exit(etx_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("praneeth");
MODULE_DESCRIPTION("procfs Example");

