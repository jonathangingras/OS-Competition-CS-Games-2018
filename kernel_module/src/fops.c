#include "module.h"


/*
  File operations table for the character device
 */
int dev_open(struct inode *, struct file *);
int dev_release(struct inode *, struct file *);
ssize_t dev_read(struct file *, char *, size_t, loff_t*);
long dev_ioctl(struct file *, unsigned int, unsigned long);

struct file_operations file_operations = {
  .open = dev_open,
  .release = dev_release,
  .read = dev_read,
  .unlocked_ioctl = dev_ioctl,
};
