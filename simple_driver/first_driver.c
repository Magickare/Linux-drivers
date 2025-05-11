  #include <linux/module.h>
  #include <linux/kernel.h>

  MODULE_LICENSE("GPL");
  MODULE_AUTHOR("Siddhu");
  MODULE_DESCRIPTION("A Simple Linux Device Driver");
  MODULE_VERSION("1.0");

  static int __init first_driver_init(void) {
      printk(KERN_INFO "First Driver: Initialized\n");
      return 0;
  }

  static void __exit first_driver_exit(void) {
      printk(KERN_INFO "First Driver: Exited\n");
  }

  module_init(first_driver_init);
  module_exit(first_driver_exit);

