#include "common.hh"

TEST_F(Deinit, canDeinitDeviceWithoutCrash) {
  kiki_handle_t *dev;

  int ret = kiki_device_init(&dev);
  if(ret != 0) {
    throw std::runtime_error("could not init!");
  }

  kiki_device_deinit(dev);
}
