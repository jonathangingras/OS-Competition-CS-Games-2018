#include "../module.h"

/*
  Changes the current buffer selection to the id provided
  The user should provide an unsigned long corresponding to the desired buffer's id
  This buffer should already exist in device
  On success, this ioctl sets status to KIKIST_BUFSELECTED
  It must be called every time a subsequent call needing KIKIST_BUFSELECTED status

  may fail at any time
 */
int kiki_selbuf(unsigned int no, void *data) {
  unsigned long id = (unsigned long)data;

  if(random_fail()) {
    set_status(KIKIERR_FAILED_SELBUF, "failed at selecting buffer");
    return KIKIERR_FAILED_SELBUF;
  }

  if(!buffer_id_present(id)) {
    set_status(KIKIERR_FAILED_SELBUF, "no such buffer");
    return KIKIERR_FAILED_SELBUF;
  }

  buffer_select(id);

  correction_stats.select_buffer_called += 1;

  return 0;
}
