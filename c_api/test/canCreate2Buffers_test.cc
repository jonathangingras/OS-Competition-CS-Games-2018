#include "common.hh"

TEST_F(NewBuffer, canCreate2Buffers) {
  kiki_buffer_handle_t *buffer1 = NULL, *buffer2 = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer1);

  ASSERT_EQ(0, ret) << "new buffer1 returned non zero";
  ASSERT_NE((void*)NULL, buffer1) << "buffer pointer is null";

  ret = kiki_new_buffer(dev, 256, &buffer2);

  ASSERT_EQ(0, ret) << "new buffer2 returned non zero";
  ASSERT_NE((void*)NULL, buffer2) << "buffer pointer is null";

  GetCorrectionStats();

  EXPECT_EQ(2, correction_stats.create_buffer_called);
}
