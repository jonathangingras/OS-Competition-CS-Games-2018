#include "common.hh"

TEST_F(Init, cannotInitDeviceTwice) {
  kiki_handle_t *dev;

  int ret = kiki_device_init(&dev);
  ret = kiki_device_init(&dev);

  EXPECT_EQ(-2, ret);
}
