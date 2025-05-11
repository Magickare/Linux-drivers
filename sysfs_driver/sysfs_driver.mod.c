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
	{ 0x33e1b54d, "sysfs_remove_file_ns" },
	{ 0x4a165127, "kobject_put" },
	{ 0x376e47a6, "sysfs_create_file_ns" },
	{ 0x6fabae87, "kobject_create_and_add" },
	{ 0x9e03848f, "kernel_kobj" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E56D81D721D8246531B5A88");
