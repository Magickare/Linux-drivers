#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("A Simple Workqueue example");

static struct workqueue_struct *my_workqueue;
static void workqueue_function(struct work_struct *work);

DECLARE_WORK(my_work, workqueue_function);

static void workqueue_function(struct work_struct *work)
{
    pr_info("Workqueue function running in background\n");
    msleep(5000);  
    pr_info("Workqueue function completed\n");
}

static int __init my_workqueue_init(void)
{
    pr_info("Initializing Custom Workqueue Module\n");
    my_workqueue = alloc_workqueue("my_wq", WQ_UNBOUND, 1);
    if (my_workqueue)
        queue_work(my_workqueue, &my_work);
    return 0;
}

static void __exit my_workqueue_exit(void)
{
    flush_workqueue(my_workqueue);
    destroy_workqueue(my_workqueue);
    pr_info("Exiting Custom Workqueue Module\n");
}

module_init(my_workqueue_init);
module_exit(my_workqueue_exit);

