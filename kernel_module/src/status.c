#include "module.h"


struct kiki_status status_ = {
  .status_no = 0,
  .status_msg = "idle",
};

unsigned int get_status(void) {
  return status_.status_no;
}

void set_status(unsigned int no, const char *msg) {
  status_.status_no = no;
  memcpy(status_.status_msg, msg, strlen(msg) + 1);
}

void reset_status(void) {
  set_status(KIKIST_IDLE, "idle");
}
