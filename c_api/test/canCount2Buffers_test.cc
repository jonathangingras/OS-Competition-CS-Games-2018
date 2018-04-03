#include "common.hh"

TEST_F(CountBuffers, canCount2Buffers) {
  kiki_buffer_handle_t *buffer1 = NULL, *buffer2 = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer1);

  ASSERT_EQ(0, ret) << "new buffer1 returned non zero";

  ret = kiki_new_buffer(dev, 256, &buffer2);

  ASSERT_EQ(0, ret) << "new buffer2 returned non zero";

  ResetCorrectionStats();

  size_t count;
  ret = kiki_count_buffers(dev, &count);

  GetCorrectionStats();

  EXPECT_EQ(1, correction_stats.count_buffers_called);

  ASSERT_EQ(0, ret) << "count buffers did not return 0";
  ASSERT_EQ(size_t(2), count);
}
