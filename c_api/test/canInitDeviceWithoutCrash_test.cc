#include "common.hh"

TEST_F(Init, canInitDeviceWithoutCrash) {
  kiki_handle_t *dev;

  int ret = kiki_device_init(&dev);

  EXPECT_EQ(0, ret);
}
