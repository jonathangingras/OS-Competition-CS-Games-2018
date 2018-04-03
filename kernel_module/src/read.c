#include "module.h"


static char *hidden_data = "The kiki device does not support the read/write interface. In order to use it, you should use the ioctl interface";

ssize_t dev_read(struct file *file, char *buffer, size_t length, loff_t *offset) {
  int err = 0;

  if(length > strlen(hidden_data)) {
    printk(KERN_ALERT "kiki: user space asked to read too much\n");
    return -EFAULT;
  }

  if((err = copy_to_user(buffer, hidden_data, length))) {
    printk(KERN_ALERT "kiki: could not copy data to user space\n");
    return -EFAULT;
  }

  printk(KERN_INFO "kiki: sent data to user space successfully\n");

  return length;
}
