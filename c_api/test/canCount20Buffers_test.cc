#include "common.hh"

TEST_F(CountBuffers, canCount20Buffers) {
  std::vector<kiki_buffer_handle_t *> buffers;
  buffers.reserve(20);
  int ret;

  for(int i = 0; i < 20; ++i) {
    kiki_buffer_handle_t *buffer = NULL;

    ret = kiki_new_buffer(dev, 256, &buffer);

    ASSERT_EQ(0, ret) << "new buffer returned non zero";

    buffers.push_back(buffer);
  }

  GetCorrectionStats();

  EXPECT_EQ(20, correction_stats.create_buffer_called);

  size_t count;
  ret = kiki_count_buffers(dev, &count);

  ASSERT_EQ(0, ret) << "count buffers did not return 0";
  ASSERT_EQ(size_t(20), count);
}
