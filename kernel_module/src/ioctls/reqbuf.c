#include "../module.h"

/*
  Requests the creation of a buffer in the device
  The user should provide a pointer to a "struct kiki_buffer_request" in user space
  memory containing appropriate information.

  may fail at any time
 */
int kiki_reqbuf(unsigned int no, void *data) {
  int err;
  struct kiki_buffer *buf;
  struct kiki_buffer_request request;

  printk(KERN_INFO "kiki: reqbuff\n");

  if(random_fail()) {
    set_status(KIKIERR_FAILED_REQBUF, "failed requiring buffer");
    return KIKIERR_FAILED_REQBUF;
  }

  copy_from_user(&request, data, sizeof(request));

  buf = buffer_new(request.id, request.size);
  if(!buf) {
    set_status(KIKIERR_FAILED_REQBUF, "kmalloc failed");
    return KIKIERR_FAILED_REQBUF;
  }

  if((err = buffer_list_append(buf))) {
    set_status(KIKIERR_FAILED_REQBUF, "appending buffer list failed");
    buffer_free(buf);
    return KIKIERR_FAILED_REQBUF;
  }

  correction_stats.create_buffer_called += 1;

  return 0;
}
