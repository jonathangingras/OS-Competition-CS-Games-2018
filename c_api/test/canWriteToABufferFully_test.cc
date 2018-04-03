#include "common.hh"

TEST_F(Write, canWriteToABufferFully) {
  kiki_buffer_handle_t *buffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  char data[256] = "some buffer data";
  ret = kiki_write_buffer(buffer, data, 256);

  EXPECT_EQ(256, ret) << "write returned not the good data size";

  GetCorrectionStats();
  EXPECT_LE(1, correction_stats.select_buffer_called) << "select buffer not called";
  EXPECT_LE(1, correction_stats.set_listen_state_called) << "listen state not called";
  EXPECT_EQ(1, correction_stats.fill_called) << "fill not called";
}
