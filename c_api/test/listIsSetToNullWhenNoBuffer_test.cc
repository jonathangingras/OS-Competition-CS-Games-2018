#include "common.hh"

TEST_F(ListBuffers, listIsSetToNullWhenNoBuffer) {
  kiki_buffer_handle_t **buffers;

  int ret = kiki_list_buffers(dev, &buffers);

  ASSERT_EQ(0, ret) << "list buffers did not return 0";

  EXPECT_EQ(NULL, buffers);
}
