#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbetronicX");
MODULE_DESCRIPTION("Dynamic Workqueue Example");

static struct workqueue_struct *my_workqueue;
static struct work_struct my_work;

static void workqueue_handler(struct work_struct *work)
{
    pr_info("Workqueue is running in process context. jiffies = %ld\n", jiffies);
}

static int __init my_workqueue_init(void)
{
    pr_info("Initializing dynamic workqueue example...\n");

    // Create workqueue
    my_workqueue = create_workqueue("my_queue");
    if (!my_workqueue) {
        pr_err("Failed to create workqueue\n");
        return -ENOMEM;
    }

    INIT_WORK(&my_work, workqueue_handler);

    // Queue the work
    queue_work(my_workqueue, &my_work);

    return 0;
}

static void __exit my_workqueue_exit(void)
{
    flush_workqueue(my_workqueue);
    destroy_workqueue(my_workqueue);
    pr_info("Exiting dynamic workqueue example\n");
}

module_init(my_workqueue_init);
module_exit(my_workqueue_exit);

