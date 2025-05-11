#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Own Workqueue Example");

static struct workqueue_struct *own_workqueue;

void workqueue_fn(struct work_struct *work);
DECLARE_WORK(workqueue_task, workqueue_fn);

void workqueue_fn(struct work_struct *work)
{
    pr_info("Workqueue Function Running in Process Context\n");
    ssleep(5);
    pr_info("Workqueue Function Completed\n");
}

static int __init my_workqueue_init(void)  
{
    pr_info("Module Inserted\n");
    
    own_workqueue = create_workqueue("own_queue");
    if (!own_workqueue) {
        pr_err("Workqueue creation failed\n");
        return -ENOMEM;
    }

    queue_work(own_workqueue, &workqueue_task);
    return 0;
}

static void __exit my_workqueue_exit(void) 
{
    flush_workqueue(own_workqueue);
    destroy_workqueue(own_workqueue);
    pr_info("Module Removed\n");
}

module_init(my_workqueue_init);   
module_exit(my_workqueue_exit);   

