#include "module.h"


/*
  uevent permissions for device class
*/
int dev_uevent(struct device *dev, struct kobj_uevent_env *env);


static int __init init(void);
module_init(init);

int __init init(void) {
  printk(KERN_INFO "kiki: module starting to load\n");

  /* allocate device major number */
  if((device_major_number = register_chrdev(0, KIKI_DEVICE_NAME, &file_operations)) < 0) {
    printk(KERN_ALERT "kiki: could not register device, failling\n");
    return device_major_number;
  }
  printk(KERN_INFO "kiki: character device registered successfully\n");

  /* register device class */
  if(IS_ERR((device_class = class_create(THIS_MODULE, KIKI_DEVICE_CLASS_NAME)))) {
    unregister_chrdev(device_major_number, KIKI_DEVICE_NAME);
    printk(KERN_ALERT "kiki: could not register device class, failling\n");
    return PTR_ERR(device_class);
  }
  printk(KERN_INFO "kiki: device class registered successfully\n");

  device_class->dev_uevent = &dev_uevent; /* set uevent permissions */

  /* create device */
  if(IS_ERR((device = device_create(device_class,
                                    NULL,
                                    MKDEV(device_major_number, 0),
                                    NULL,
                                    KIKI_DEVICE_NAME)))) {
    class_destroy(device_class);
    unregister_chrdev(device_major_number, KIKI_DEVICE_NAME);
    printk(KERN_ALERT "kiki: could not create device\n");
    return PTR_ERR(device);
  }
  buffer_list_init();

  printk(KERN_INFO "kiki: device created successfully\n");

  printk(KERN_INFO "kiki: module loaded successfully\n");

  kiki_correction_stats_init();

  return 0;
}
