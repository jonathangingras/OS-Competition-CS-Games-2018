#include "common.hh"

TEST_F(Deinit, canReinitAfterDeinitWithoutCrash) {
  kiki_handle_t *dev;

  int ret = kiki_device_init(&dev);
  if(ret != 0) {
    throw std::runtime_error("could not init!");
  }

  kiki_device_deinit(dev);

  EXPECT_EQ(0, kiki_device_init(&dev));
}
