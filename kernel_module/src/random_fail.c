#include "module.h"
#include <linux/random.h>


int random_fail(void) {
  unsigned int i;

  get_random_bytes(&i, sizeof(i));

  return i % 2;
}
