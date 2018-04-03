#include "module.h"

/*
  module properties
*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonathan Gingras");
MODULE_DESCRIPTION("An attempt to kiki with the kernel");
MODULE_VERSION("0.0.1");


int device_major_number = 0; /* character device major number */
struct class *device_class; /* character device driver-driven class */
struct device *device = NULL; /* pointer to device */
DEFINE_MUTEX(mutex);
