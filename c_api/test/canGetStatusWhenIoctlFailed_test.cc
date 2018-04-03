#include "common.hh"

TEST_F(GetStatusTest, canGetStatusWhenIoctlFailed) {
  while(ioctl(kiki_device_fileno(dev), KIKIIO_SETSTATELIS) == 0);

  int ret = kiki_device_get_status(dev, &status);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(10, status.status_no);
  EXPECT_STREQ("failed setting the device to listening state", status.status_msg);
}
