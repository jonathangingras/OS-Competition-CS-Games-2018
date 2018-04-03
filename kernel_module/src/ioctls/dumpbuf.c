#include "../module.h"

/*
  Dumps the currently selected buffer to user space memory
  The user should provide a pointer to user space memory in order
  to dump buffer in it. The provided memory should be large enough to
  contain the buffer entirely.

  Device should be put in Answering State to call this ioctl

  may fail at any moment
 */
int kiki_dumpbuf(unsigned int no, void *data) {
  unsigned long id;
  struct kiki_buffer *buf;

  if(get_state() != KIKI_STATEANS) {
    set_status(KIKIERR_FAILED_DUMPBUF, "device in wrong state");
    return KIKIERR_FAILED_DUMPBUF;
  }

  if(buffer_selection(&id)) {
    set_status(KIKIERR_FAILED_DUMPBUF, "no buffer selected to dump");
    return KIKIERR_FAILED_DUMPBUF;
  }

  if(random_fail()) {
    set_status(KIKIERR_FAILED_DUMPBUF, "failed dumping buffer");
    return KIKIERR_FAILED_DUMPBUF;
  }

  buf = buffer_get(id);

  if(!buf) {
    set_status(KIKIERR_FAILED_DUMPBUF, "no such buffer id");
    return KIKIERR_FAILED_DUMPBUF;
  }

  copy_to_user(data, buf->data, buf->length);
  buffer_touch(buf);

  correction_stats.dump_called += 1;

  return 0;
}
