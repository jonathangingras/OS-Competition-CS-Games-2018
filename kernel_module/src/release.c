#include "module.h"


int dev_release(struct inode *inode, struct file *file) {
  reset_status();
  mutex_unlock(&mutex);
  printk(KERN_INFO "kiki: closed device\n");
  return 0;
}
