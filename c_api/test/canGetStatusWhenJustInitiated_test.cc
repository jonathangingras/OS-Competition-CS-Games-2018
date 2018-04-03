#include "common.hh"

TEST_F(GetStatusTest, canGetStatusWhenJustInitiated) {
  int ret = kiki_device_get_status(dev, &status);

  EXPECT_EQ(0, ret);
  EXPECT_EQ(0, status.status_no);
  EXPECT_STREQ("idle", status.status_msg);
}
