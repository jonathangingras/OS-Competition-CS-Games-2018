#include "../module.h"


/*
  Sets the current device state to LIS
  The user should pass no argument

  may fail at any moment
*/
int kiki_setstatelis(unsigned int no, void *data) {
  if(random_fail()) {
    set_status(KIKIERR_FAILED_SETSTATE, "failed setting the device to listening state");
    return KIKIERR_FAILED_SETSTATE;
  }

  set_state(KIKI_STATELIS);

  correction_stats.set_listen_state_called += 1;

  return 0;
}
