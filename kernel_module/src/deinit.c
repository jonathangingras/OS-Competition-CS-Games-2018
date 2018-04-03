#include "module.h"


static void __exit deinit(void);
module_exit(deinit);

void __exit deinit(void) {
  reset_device();

  device_destroy(device_class, MKDEV(device_major_number, 0));
  class_unregister(device_class);
  class_destroy(device_class);
  unregister_chrdev(device_major_number, KIKI_DEVICE_NAME);

  printk(KERN_INFO "kiki: unloaded module\n");
}
