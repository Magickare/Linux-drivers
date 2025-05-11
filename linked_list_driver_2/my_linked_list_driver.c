#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siddhu");
MODULE_DESCRIPTION("Custom Linked List Example in Kernel");
MODULE_VERSION("1.0");

struct student {
    int roll_no;
    char name[20];
    struct list_head list;
};

static LIST_HEAD(student_list);

static int __init my_list_init(void)
{
    struct student *stud;
    int i;

    printk(KERN_INFO "Loading custom linked list module...\n");

    // Create 5 students
    for (i = 1; i <= 5; i++) {
        stud = kmalloc(sizeof(*stud), GFP_KERNEL);
        if (!stud) {
            printk(KERN_ERR "Memory allocation failed\n");
            return -ENOMEM;
        }

        stud->roll_no = 100 + i;
        snprintf(stud->name, sizeof(stud->name), "Student%d", i);
        INIT_LIST_HEAD(&stud->list);
        list_add_tail(&stud->list, &student_list);

        printk(KERN_INFO "Added: Roll No=%d, Name=%s\n", stud->roll_no, stud->name);
    }

    return 0;
}

static void __exit my_list_exit(void)
{
    struct student *stud, *tmp;

    printk(KERN_INFO "Removing custom linked list module...\n");

    list_for_each_entry_safe(stud, tmp, &student_list, list) {
        printk(KERN_INFO "Freeing: Roll No=%d, Name=%s\n", stud->roll_no, stud->name);
        list_del(&stud->list);
        kfree(stud);
    }
}

module_init(my_list_init);
module_exit(my_list_exit);

