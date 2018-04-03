#include "common.hh"

TEST_F(ListBuffers, listIsNotNullWhenHasMultipleElements) {
  kiki_buffer_handle_t **buffers;
  std::vector<kiki_buffer_handle_t *> buffers_;
  buffers_.reserve(20);
  int ret;

  for(int i = 0; i < 20; ++i) {
    kiki_buffer_handle_t *buf;
    ret = kiki_new_buffer(dev, 256, &buf);
    ASSERT_EQ(0, ret) << "new buffer returned non zero";
    GetCorrectionStats();
    ASSERT_EQ(i+1, correction_stats.create_buffer_called) << "buffers were not effectively created";
    buffers_.push_back(buf);
  }

  ret = kiki_list_buffers(dev, &buffers);
  ASSERT_EQ(0, ret) << "list buffers did not return 0";

  for(size_t i = 0; i < 20; ++i) {
    EXPECT_NE((void *)NULL, buffers[i]);
  }
}
