#include "common.hh"

TEST_F(NewBuffer, canCreateNewBuffer) {
  kiki_buffer_handle_t *buffer = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";
}
