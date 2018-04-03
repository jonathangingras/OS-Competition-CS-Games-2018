#include "../module.h"


/*
  Returns the current device state LIS, ANS or NIL
  The user should pass a pointer to a integer in user space memory
  in order for the ioctl to write it

  never fails
 */
int kiki_getstate(unsigned int no, void *data) {
  int state;

  state = get_state();
  copy_to_user((int *)data, &state, sizeof(state));

  return 0;
}
