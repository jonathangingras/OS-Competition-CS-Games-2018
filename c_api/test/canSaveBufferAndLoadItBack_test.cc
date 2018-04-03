#include "common.hh"

TEST_F(SaveBuffer, canSaveBufferAndLoadItBack) {
  kiki_buffer_handle_t *buffer = NULL, *rbuffer = NULL;
  int ret = kiki_new_buffer(dev, 256, &buffer);

  ASSERT_EQ(0, ret) << "new buffer returned non zero";
  ASSERT_NE((void*)NULL, buffer) << "buffer pointer is null";

  char data[256] = "some buffer data";
  ret = kiki_write_buffer(buffer, data, 256);

  EXPECT_EQ(256, ret) << "write returned not the good data size";

  FILE *out = fopen("TESTFILE", "wb");

  ret = kiki_save_buffer(buffer, out);
  EXPECT_EQ(0, ret) << "save buffer did not return 0";
  fclose(out);


  ResetBuffers();


  FILE *in = fopen("TESTFILE", "rb");
  ASSERT_NE((void*)NULL, in) << "cannot reopen file in reading mode";

  ret = kiki_load_buffer(dev, &rbuffer, in);
  EXPECT_EQ(0, ret) << "load buffer did not return 0";
}
