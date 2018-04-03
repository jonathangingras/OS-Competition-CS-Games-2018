#include "../module.h"


struct accumulator {
  unsigned long *output;
  unsigned long offset;
};

int append_buffer_id(struct kiki_buffer *buf, void *accumulator_ptr) {
  struct accumulator *accumulator;
  accumulator = accumulator_ptr;

  copy_to_user(accumulator->output + accumulator->offset, &buf->id, sizeof(buf->id));

  accumulator->offset++;

  return 0;
}


/*
  Lists buffers ids currently existing in device
  The user should provide a pointer (array) of unsigned long in user space
  memory in order for the ioctl to fill it. The given array should be large enough
  to contain all the ids.

  may fail at any time (but not during the filling)
 */
int kiki_listbuf(unsigned int no, void *data) {
  struct accumulator accumulator;

  if(random_fail()) {
    set_status(KIKIERR_FAILED_LISTBUF, "failed listing buffers");
    return KIKIERR_FAILED_LISTBUF;
  }

  accumulator.output = data;
  accumulator.offset = 0;

  buffer_list_foreach(append_buffer_id, &accumulator);

  return 0;
}
