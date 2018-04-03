#include "common.hh"

TEST_F(CountBuffers, countIoctlIsEffectivelyCalled) {
  size_t count;
  int ret = kiki_count_buffers(dev, &count);

  ASSERT_EQ(0, ret) << "count buffers did not return 0";

  GetCorrectionStats();

  EXPECT_EQ(1, correction_stats.count_buffers_called);
}
