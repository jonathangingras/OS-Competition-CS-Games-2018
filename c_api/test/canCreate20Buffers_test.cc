#include "common.hh"

TEST_F(NewBuffer, canCreate20Buffers) {
  std::vector<kiki_buffer_handle_t *> buffers;
  buffers.reserve(20);

  for(int i = 0; i < 20; ++i) {
    kiki_buffer_handle_t *buffer = NULL;

    int ret = kiki_new_buffer(dev, 256, &buffer);

    ASSERT_EQ(0, ret) << "new buffer returned non zero";
    ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

    buffers.push_back(buffer);
  }

  GetCorrectionStats();

  EXPECT_EQ(20, correction_stats.create_buffer_called);
}
