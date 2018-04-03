#include "common.hh"

TEST_F(Write, cannotWriteIfSizeGreaterThanMax) {
  kiki_buffer_handle_t *buffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  std::string data = "some buffer data";
  ret = kiki_write_buffer(buffer, data.c_str(), 256 + 1);

  EXPECT_NE(0, ret) << "write returned non zero";
}
