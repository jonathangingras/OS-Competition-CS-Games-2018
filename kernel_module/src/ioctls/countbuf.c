#include "../module.h"

/*
  Counts the number of existing buffers on the device
  User must provide an unsigned long pointer to user space memory
  in order to write the result in it

  may fail at any time
 */
int kiki_countbuf(unsigned int no, void *data) {
  unsigned long count;

  if(random_fail()) {
    set_status(KIKIERR_FAILED_COUNTBUF, "failed counting buffers");
    return KIKIERR_FAILED_COUNTBUF;
  }

  count = buffer_list_count();
  copy_to_user(data, &count, sizeof(count));

  correction_stats.count_buffers_called += 1;

  return 0;
}
