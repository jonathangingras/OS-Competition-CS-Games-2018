#include "common.hh"

TEST_F(CountBuffers, countIsZeroAfterInit) {
  size_t count;
  int ret = kiki_count_buffers(dev, &count);

  ASSERT_EQ(0, ret) << "count buffers did not return 0";

  EXPECT_EQ(size_t(0), count);
}
