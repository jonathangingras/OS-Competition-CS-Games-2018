#include "correction_stats_struct.h"

struct kiki_correction_stats correction_stats;

void kiki_correction_stats_reset(void);

void kiki_correction_stats_init(void) {
  kiki_correction_stats_reset();
}

void kiki_correction_stats_reset(void) {
  correction_stats.get_status_called = 0;
  correction_stats.clear_buffers_called = 0;
  correction_stats.count_buffers_called = 0;
  correction_stats.create_buffer_called = 0;
  correction_stats.inspect_called = 0;
  correction_stats.select_buffer_called = 0;
  correction_stats.set_listen_state_called = 0;
  correction_stats.set_answer_state_called = 0;
  correction_stats.fill_called = 0;
  correction_stats.dump_called = 0;
}
