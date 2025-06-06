#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x6ad771c3, "module_layout" },
	{ 0x11eb121f, "cdev_del" },
	{ 0x15659e9d, "device_destroy" },
	{ 0x8a23e3a5, "kthread_stop" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xb3f0559, "class_destroy" },
	{ 0x3d37116f, "wake_up_process" },
	{ 0xd10a0a5f, "kthread_create_on_node" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x70eb7a97, "device_create" },
	{ 0x52ea150d, "__class_create" },
	{ 0x646eac6, "cdev_add" },
	{ 0xd90cd7e6, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x1000e51, "schedule" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x800473f, "__cond_resched" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5715A052F3874E7F3D4043D");
