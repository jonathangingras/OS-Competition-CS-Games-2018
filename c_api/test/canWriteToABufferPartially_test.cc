#include "common.hh"

TEST_F(Write, canWriteToABufferPartially) {
  kiki_buffer_handle_t *buffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  std::string data = "some buffer data";
  ret = kiki_write_buffer(buffer, data.c_str(), data.size());

  EXPECT_EQ(data.size(), size_t(ret)) << "write returned not the good data size";

  GetCorrectionStats();
  EXPECT_LE(1, correction_stats.select_buffer_called) << "select buffer not called";
  EXPECT_LE(1, correction_stats.set_listen_state_called) << "listen state not called";
  EXPECT_EQ(1, correction_stats.fill_called) << "fill not called";
}
