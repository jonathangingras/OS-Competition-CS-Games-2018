#include "common.hh"

TEST_F(ClearBuffers, clearBuffersGetsEffectivelyCalled) {
  int ret = kiki_device_clear_buffers(dev);

  ASSERT_EQ(0, ret) << "clear buffer did not return 0";

  GetCorrectionStats();

  EXPECT_EQ(1, correction_stats.clear_buffers_called);
}
