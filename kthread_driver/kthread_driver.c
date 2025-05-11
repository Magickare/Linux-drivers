#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *etx_thread;

int thread_function(void *data)
{
    while (!kthread_should_stop()) {
        pr_info("Kernel Thread Running...\n");
        ssleep(5);
    }
    pr_info("Kernel Thread Stopping\n");
    return 0;
}

static int __init kthread_driver_init(void)
{
    pr_info("Kernel Thread Example Init\n");

    etx_thread = kthread_create(thread_function, NULL, "etx_kthread");
    if (etx_thread) {
        wake_up_process(etx_thread);
    } else {
        pr_err("Failed to create the thread\n");
    }

    return 0;
}

static void __exit kthread_driver_exit(void)
{
    if (etx_thread) {
        kthread_stop(etx_thread);
        pr_info("Kernel Thread Stopped\n");
    }

    pr_info("Kernel Thread Example Exit\n");
}

module_init(kthread_driver_init);
module_exit(kthread_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Kernel Thread Example");

