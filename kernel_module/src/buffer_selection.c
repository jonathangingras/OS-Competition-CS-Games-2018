#include "module.h"

static unsigned long selection;

void buffer_select(unsigned long id) {
  selection = id;
  set_status(KIKIST_BUFSELECTED, "buffer selected");
}

int buffer_selection(unsigned long *id) {
  if(get_status() == KIKIST_BUFSELECTED) {
    if(id) {
      *id = selection;
      return 0;
    }
    return -2;
  }
  return -1;
}

void buffer_clear_selection(void) {
  set_status(KIKIST_IDLE, "idle");
}
