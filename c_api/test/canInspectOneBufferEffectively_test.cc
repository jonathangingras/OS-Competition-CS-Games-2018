#include "common.hh"

TEST_F(Inspect, canInspectOneBufferEffectively) {
  kiki_buffer_handle_t *buffer = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";

  struct kiki_buffer_info info;
  ret = kiki_buffer_inspect(buffer, &info);

  ASSERT_EQ(0, ret) << "inspect returned non zero";
  ASSERT_NE(uint64_t(0), kiki_buffer_id(buffer)) << "buffer id was zero";

  GetCorrectionStats();
  EXPECT_EQ(1, correction_stats.inspect_called) << "inspect not called effectively";
}
