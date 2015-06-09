#include "carp.h"

#include <stdio.h>
#include <sys/time.h>

carp_info_t *info;

void init() {
  set_rules_active(32);
  counter_reset(0);

  store(0);
    config();
    step(50000);
    readback();
    swap_cell_storage();
    develop();
    read_types();
    read_states();
    counter_increment(0);
    jump_equal(20, 0, 10000);
    jump(0);
  end();

  store(20);
    break_out();
  end();
}

double measure_speed_seconds() {
  struct timeval t0, t1;
  gettimeofday(&t0, NULL);

  jump(0);

  for (int i = 0; i < 10000; i++) {
    matrix_dispose(get_types());
    matrix_dispose(get_states());
  }

  gettimeofday(&t1, NULL);
  int diffus = (t1.tv_sec*1000000 + t1.tv_usec) - (t0.tv_sec*1000000 + t0.tv_usec);
  double time = (double)diffus / 1000000;
  return time;
}

void profile() {
  init();

  printf("Profiling development and step performance...\n");
  printf("Time: %f seconds\n", measure_speed_seconds());
}

int main() {
  info = carp_connect();
  carp_reset();
  profile();
  carp_disconnect();
  return 0;
}
