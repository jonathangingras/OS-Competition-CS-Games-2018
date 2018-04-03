#include "../module.h"

/*
  Returns the current status of the device,
  the status is more like an error code
  The status does influence the ability to call certain ioctls

  never fails
 */
int kiki_get_status(unsigned int no, void *data) {
  int err = 0;

  if((err = copy_to_user(data, &status_, sizeof(status_)))) {
    printk(KERN_ALERT "kiki: could not copy to user\n");
    return err;
  }

  correction_stats.get_status_called += 1;

  return 0;
}
