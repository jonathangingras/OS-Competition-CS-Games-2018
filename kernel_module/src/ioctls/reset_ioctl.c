#include "../module.h"


/*
  Resets the device entire internal state

  never fails
*/
int kiki_reset(unsigned int no, void *data) {
  reset_device();

  return 0;
}
