#include "../module.h"

/*
  May not be called in order to maintain the device functioning properly
 */
int kiki_do_not_call(unsigned int no, void *data) {
  panic("i told you so...");
}
