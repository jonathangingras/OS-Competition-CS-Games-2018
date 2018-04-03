#include "module.h"


static int state;

int get_state(void) {
  return state;
}

void set_state(int _state) {
  state = _state;
}

void reset_state(void) {
  state = KIKI_STATENIL;
}
