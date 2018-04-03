#include "../module.h"


/*
  Sets the current device state to ANS
  The user should pass no argument

  may fail at any moment
*/
int kiki_setstateans(unsigned int no, void *data) {
  if(random_fail()) {
    set_status(KIKIERR_FAILED_SETSTATE, "failed setting the device to answering state");
    return KIKIERR_FAILED_SETSTATE;
  }

  set_state(KIKI_STATEANS);

  correction_stats.set_answer_state_called += 1;

  return 0;
}
