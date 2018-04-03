#include "common.hh"

TEST_F(GetStatusTest, statusIsEffectivelyGotten) {
  int ret = kiki_device_get_status(dev, &status);

  GetCorrectionStats();

  EXPECT_EQ(1, correction_stats.get_status_called);
}
