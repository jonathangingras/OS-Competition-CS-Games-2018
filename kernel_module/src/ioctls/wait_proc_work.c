#include "../module.h"
#include <linux/random.h>

/*
  Gives time to device to finish its underlying tasks between other calls
  The user may call it if needed to maintain the device stability

  never fails
 */
int kiki_wait_proc_work(unsigned int no, void* data) {
  /* does purely nothing, but has a fancy name */
  /* random useless wait to piss them off */
  unsigned int msecs;
  get_random_bytes(&msecs, sizeof(msecs));
  msecs %= 20000;

  printk(KERN_INFO "kiki: wait for process %u ioctl: %u\n", current->pid, msecs);

  msleep(msecs);

  return 0;
}
