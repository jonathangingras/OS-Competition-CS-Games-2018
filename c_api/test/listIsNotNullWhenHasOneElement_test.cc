#include "common.hh"

TEST_F(ListBuffers, listIsNotNullWhenHasOneElement) {
  kiki_buffer_handle_t **buffers;
  kiki_buffer_handle_t *buf;

  int ret = kiki_new_buffer(dev, 256, &buf);

  GetCorrectionStats();
  ASSERT_EQ(1, correction_stats.create_buffer_called) << "new was not effectively called";
  ASSERT_EQ(0, ret) << "new buffer returned non zero";

  ret = kiki_list_buffers(dev, &buffers);

  ASSERT_EQ(0, ret) << "list buffers did not return 0";

  EXPECT_NE((void *)NULL, buffers);
}
