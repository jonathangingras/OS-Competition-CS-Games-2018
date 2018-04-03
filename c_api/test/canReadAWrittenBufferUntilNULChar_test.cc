#include "common.hh"

TEST_F(Read, canReadAWrittenBufferUntilNULChar) {
  kiki_buffer_handle_t *buffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  std::string wdata = "some buffer data";
  ret = kiki_write_buffer(buffer, wdata.c_str(), wdata.size());

  ASSERT_EQ(wdata.size(), size_t(ret)) << "write returned not the good data size";

  char rdata[256];
  ret = kiki_read_buffer(buffer, rdata, wdata.size());
  rdata[wdata.size()] = 0;
  EXPECT_EQ(wdata.size(), size_t(ret)) << "read returned not the good size";
  EXPECT_STREQ(wdata.c_str(), rdata);
}
