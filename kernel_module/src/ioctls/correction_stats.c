#include "../module.h"


int kiki_correction_stats(unsigned int no, void *data) {
  #ifdef CS_CORRECTION_MODE

  int err = 0;

  if((err = copy_to_user(data, &correction_stats, sizeof(correction_stats)))) {
    printk(KERN_ALERT "kiki: could not copy to user\n");
    return err;
  }

  #endif
  return 0;
}

int kiki_reset_correction_stats(unsigned int no, void *data) {
#ifdef CS_CORRECTION_MODE

  kiki_correction_stats_reset();

#endif
  return 0;
}
