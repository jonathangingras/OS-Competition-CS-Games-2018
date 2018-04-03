#include "common.hh"

TEST_F(Size, bufferSizeIsOk) {
  kiki_buffer_handle_t *buffer = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";

  size_t size;
  ret = kiki_buffer_size(buffer, &size);

  ASSERT_EQ(0, ret) << "size returned non zero";

  ASSERT_EQ(size_t(256), size) << "buffer id was zero";
}
