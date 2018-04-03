#include "module.h"


void reset_device(void) {
  reset_status();
  reset_state();
  buffer_clear_selection();
  buffer_list_clear();
}
