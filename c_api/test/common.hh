#ifndef CORRECTION_COMMON_HH
#define CORRECTION_COMMON_HH

#include <sys/ioctl.h>
#include <iostream>

#include <gtest/gtest.h>

#include "../include/kiki_api.h"
#include "../../kernel_module/src/correction_stats_struct.h"

#include <algorithm>


namespace cs18os {

class Test: public ::testing::Test {
protected:
  struct kiki_status status;

  kiki_handle_t *dev;

  struct kiki_correction_stats correction_stats;


  inline void ResetCorrectionStats() {
    ioctl(kiki_device_fileno(dev), 0x28b);
  }

  inline void GetCorrectionStats() {
    ioctl(kiki_device_fileno(dev), 0x28a, &correction_stats);
  }

  inline void ResetBuffers() {
    ioctl(kiki_device_fileno(dev), KIKIIO_RST);
  }


  void SetUp() {
    memset(&status, 0, sizeof(status));

    int ret = kiki_device_init(&dev);

    if(ret != 0) {
      throw std::runtime_error("non zero init return");
    }

    ResetBuffers();
    ResetCorrectionStats();
  }

  void TearDown() {
    kiki_device_deinit(dev);
  }
};

}

class ClearBuffers: public cs18os::Test {
};

class CountBuffers: public cs18os::Test {
};

class Deinit: public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}
};

class GetStatusTest: public cs18os::Test {
};

class Id: public cs18os::Test {};

class Init: public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}
};

class Inspect: public cs18os::Test {
};

class ListBuffers: public cs18os::Test {
protected:

  void TearDown() {
    ResetBuffers();
    cs18os::Test::TearDown();
  }
};

class NewBuffer: public cs18os::Test {
protected:

  void TearDown() {
    ResetBuffers();
    cs18os::Test::TearDown();
  }
};

class Read: public cs18os::Test {};

class SaveBuffer: public cs18os::Test {};

class Size: public cs18os::Test {
};

class Write: public cs18os::Test {};

#endif
