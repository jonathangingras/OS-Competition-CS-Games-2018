#include "../module.h"

/*
  Clears all the existing buffers on the device

  may fail at any time
 */
int kiki_clearbufs(unsigned int no, void *data) {
  if(random_fail()) {
    set_status(KIKIERR_FAILED_CLRBUF, "failed clearing buffers");
    return KIKIERR_FAILED_CLRBUF;
  }

  buffer_list_clear();

  correction_stats.clear_buffers_called += 1;

  return 0;
}
