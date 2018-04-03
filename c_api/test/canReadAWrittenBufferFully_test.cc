#include "common.hh"

TEST_F(Read, canReadAWrittenBufferFully) {
  kiki_buffer_handle_t *buffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  char wdata[256];
  ret = kiki_write_buffer(buffer, wdata, 256);

  ASSERT_EQ(256, ret) << "write returned not the good data size";

  char rdata[256];
  ret = kiki_read_buffer(buffer, rdata, 256);
  EXPECT_EQ(256, ret) << "read returned not the good size";
  EXPECT_EQ(0, memcmp(wdata, rdata, 256));
}
