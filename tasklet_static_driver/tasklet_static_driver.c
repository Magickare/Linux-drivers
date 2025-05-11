#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Embetronicx");
MODULE_DESCRIPTION("Tasklet Static Method Example");

// Tasklet function with the correct signature
static void tasklet_fn(struct tasklet_struct *t)
{
    pr_info("Tasklet function executed\n");
}

// Declare the tasklet statically (no data parameter in new kernels)
DECLARE_TASKLET(my_tasklet, tasklet_fn);

static int __init tasklet_static_init(void)
{
    pr_info("Tasklet Static Init\n");

    tasklet_schedule(&my_tasklet);  // Schedule tasklet

    return 0;
}

static void __exit tasklet_static_exit(void)
{
    pr_info("Tasklet Static Exit\n");

    tasklet_kill(&my_tasklet);  // Clean up
}

module_init(tasklet_static_init);
module_exit(tasklet_static_exit);

