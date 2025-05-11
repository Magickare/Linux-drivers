#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Embetronicx");
MODULE_DESCRIPTION("Linux Kernel Linked List Example");

struct student {
    int roll_no;
    char name[20];
    struct list_head list;
};

static LIST_HEAD(student_list);

static int __init linked_list_init(void) {
    struct student *stud;
    int i;

    printk(KERN_INFO "Linked List Module Init\n");

    // Adding 5 students
    for (i = 1; i <= 5; i++) {
        stud = kmalloc(sizeof(*stud), GFP_KERNEL);
        stud->roll_no = i;
        snprintf(stud->name, 20, "Student-%d", i);
        INIT_LIST_HEAD(&stud->list);
        list_add_tail(&stud->list, &student_list);
    }

    // Traverse the list
    list_for_each_entry(stud, &student_list, list) {
        printk(KERN_INFO "Roll No: %d, Name: %s\n", stud->roll_no, stud->name);
    }

    return 0;
}

static void __exit linked_list_exit(void) {
    struct student *stud, *tmp;

    printk(KERN_INFO "Linked List Module Exit\n");

    list_for_each_entry_safe(stud, tmp, &student_list, list) {
        printk(KERN_INFO "Freeing Roll No: %d, Name: %s\n", stud->roll_no, stud->name);
        list_del(&stud->list);
        kfree(stud);
    }
}

module_init(linked_list_init);
module_exit(linked_list_exit);

