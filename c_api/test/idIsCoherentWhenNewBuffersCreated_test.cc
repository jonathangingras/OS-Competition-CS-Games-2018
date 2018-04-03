#include "common.hh"

TEST_F(Id, idIsCoherentWhenNewBuffersCreated) {
  kiki_buffer_handle_t *buffer1 = NULL, *buffer2 = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer1);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer1) << "buffer pointer is null";

  ret = kiki_new_buffer(dev, 256, &buffer2);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer2) << "buffer pointer is null";

  EXPECT_NE(kiki_buffer_id(buffer1), kiki_buffer_id(buffer2)) << "buffer ids are equal";
  EXPECT_NE(uint64_t(0), kiki_buffer_id(buffer1)) << "buffer id is zero";
  EXPECT_NE(uint64_t(0), kiki_buffer_id(buffer2)) << "buffer id is zero";
}
