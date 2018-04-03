#include "../module.h"

/*
  Provides the currently selected buffer's id
  The user should provide a pointer to an unsigned long in order for the ioctl to fill it
  with the currently selected buffer's id

  may fail at any time
 */
int kiki_ioinfo(unsigned int no, void *data) {
  unsigned long id;

  if(random_fail()) {
    set_status(KIKIERR_FAILED_IOINFO, "failed giving io information");
    return KIKIERR_FAILED_IOINFO;
  }

  if(buffer_selection(&id)) {
    set_status(KIKIERR_FAILED_IOINFO, "no buffer selected");
    return KIKIERR_FAILED_IOINFO;
  }

  copy_to_user(data, &id, sizeof(id));

  return 0;
}
