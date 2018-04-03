#ifndef KIKI_CS_CORRECTION_STATS_H
#define KIKI_CS_CORRECTION_STATS_H

struct kiki_correction_stats {
  int get_status_called;
  int clear_buffers_called;
  int count_buffers_called;
  int create_buffer_called;
  int inspect_called;
  int select_buffer_called;
  int set_listen_state_called;
  int set_answer_state_called;
  int fill_called;
  int dump_called;
};

#endif
