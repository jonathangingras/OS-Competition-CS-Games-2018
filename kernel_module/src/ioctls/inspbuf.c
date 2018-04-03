#include "../module.h"

/*
  Inspects the currently selected buffer by giving information on it
  The user should provide a pointer to a "struct kiki_buffer_info" in
  user space memory in order for the ioctl to fill it

  may fail at any time
 */
int kiki_inspbuf(unsigned int no, void *data) {
  unsigned long id;
  struct kiki_buffer *buf;
  struct kiki_buffer_info output;

  if(buffer_selection(&id)) {
    set_status(KIKIERR_FAILED_INSPBUF, "no buffer selected to inspect");
    return KIKIERR_FAILED_INSPBUF;
  }

  if(random_fail()) {
    set_status(KIKIERR_FAILED_INSPBUF, "failed inspecting buffer");
    return KIKIERR_FAILED_INSPBUF;
  }

  buf = buffer_get(id);

  if(!buf) {
    set_status(KIKIERR_FAILED_INSPBUF, "no such buffer id");
    return KIKIERR_FAILED_INSPBUF;
  }

  output.id = buf->id;
  output.length = buf->length;
  output.time_created = buf->time_created;
  output.time_accessed = buf->time_accessed;
  copy_to_user(data, &output, sizeof(output));

  correction_stats.inspect_called += 1;

  return 0;
}
