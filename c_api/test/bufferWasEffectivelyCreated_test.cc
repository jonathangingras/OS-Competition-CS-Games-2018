#include "common.hh"

TEST_F(NewBuffer, bufferWasEffectivelyCreated) {
  kiki_buffer_handle_t *buffer = NULL;

  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  GetCorrectionStats();

  EXPECT_EQ(1, correction_stats.create_buffer_called);
}
