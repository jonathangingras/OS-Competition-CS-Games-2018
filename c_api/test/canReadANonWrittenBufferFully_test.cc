#include "common.hh"

TEST_F(Read, canReadANonWrittenBufferFully) {
  kiki_buffer_handle_t *buffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  char data[256];
  ret = kiki_read_buffer(buffer, data, 256);
  EXPECT_EQ(256, ret) << "read returned not the good size";
}
