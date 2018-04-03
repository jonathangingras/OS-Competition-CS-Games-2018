#include "../module.h"

/*
  Fills the currently selected buffer with user provided data
  The user should provide a pointer to a "struct kiki_buffer_fill_request" in
  user space memory containing appropriate information

  Device should be in Listening State in order to call this ioctl

  may fail at any time
 */
int kiki_fillbuf(unsigned int no, void *data) {
  unsigned long id;
  struct kiki_buffer *buf;
  struct kiki_buffer_fill_request fill_request;

  if(get_state() != KIKI_STATELIS) {
    set_status(KIKIERR_FAILED_FILLBUF, "device in wrong state");
    return KIKIERR_FAILED_FILLBUF;
  }

  if(buffer_selection(&id)) {
    set_status(KIKIERR_FAILED_FILLBUF, "no buffer selected to fill");
    return KIKIERR_FAILED_FILLBUF;
  }

  if(random_fail()) {
    set_status(KIKIERR_FAILED_FILLBUF, "failed filling buffer");
    return KIKIERR_FAILED_FILLBUF;
  }

  buf = buffer_get(id);

  if(!buf) {
    set_status(KIKIERR_FAILED_FILLBUF, "no such buffer id");
    return KIKIERR_FAILED_FILLBUF;
  }

  copy_from_user(&fill_request, data, sizeof(fill_request));

  if(fill_request.length > buf->length) {
    set_status(KIKIERR_FAILED_FILLBUF, "filling request size is too big for this buffer");
    return KIKIERR_FAILED_FILLBUF;
  }

  copy_from_user(buf->data, fill_request.data, fill_request.length);
  buffer_touch(buf);

  correction_stats.fill_called += 1;

  return 0;
}
