#include "module.h"


int dev_open(struct inode *inode, struct file *file) {
  if(mutex_trylock(&mutex)) {
    printk(KERN_INFO "kiki: opened device\n");
    return 0;
  }
  return -EBUSY;
}
