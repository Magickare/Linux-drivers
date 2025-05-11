#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Dynamic Tasklet Example for Kernel 5.15");

static struct tasklet_struct *my_tasklet;

// Correct callback type for this kernel version
static void my_tasklet_function(unsigned long data)
{
    pr_info("Tasklet function executed (dynamic method). Data = %lu\n", data);
}

static int __init tasklet_dynamic_init(void)
{
    pr_info("Tasklet Dynamic Init\n");

    // Allocate memory for the tasklet
    my_tasklet = kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
    if (!my_tasklet) {
        pr_err("Failed to allocate memory for tasklet\n");
        return -ENOMEM;
    }

    // Initialize tasklet with function and data
    tasklet_init(my_tasklet, my_tasklet_function, 1234);

    // Schedule tasklet to run
    tasklet_schedule(my_tasklet);

    return 0;
}

static void __exit tasklet_dynamic_exit(void)
{
    pr_info("Tasklet Dynamic Exit\n");

    tasklet_kill(my_tasklet);  // Ensure it's not running
    kfree(my_tasklet);         // Free the memory
}

module_init(tasklet_dynamic_init);
module_exit(tasklet_dynamic_exit);

