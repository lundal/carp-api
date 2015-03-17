#include "carp.h"

#include <stdio.h>
#include <sys/time.h>

carp_info_t *info;

double measure_ping_us() {
  int n = 100000;
  struct timeval t0, t1;
  gettimeofday(&t0, NULL);
  for (int i = 0; i < n; i++) {
    read_type(0,0,0);
    get_type(0,0,0);
  }
  gettimeofday(&t1, NULL);
  int diffus = (t1.tv_sec*1000000 + t1.tv_usec) - (t0.tv_sec*1000000 + t0.tv_usec);
  double ping = (double)diffus / (double)n;
  return ping;
}

double measure_throughput_mbps() {
  int n = 1000;
  struct timeval t0, t1;
  gettimeofday(&t0, NULL);
  read_types();
  for (int i = 1; i < n; i++) {
    read_types();
    get_types();
  }
  get_types();
  gettimeofday(&t1, NULL);
  int diffus = (t1.tv_sec*1000000 + t1.tv_usec) - (t0.tv_sec*1000000 + t0.tv_usec);
  int bits = n * info->matrix_depth * info->matrix_height * words_per_row(info->type_bits) * 32;
  double mbps = (double)(bits) / (double)diffus;
  return mbps;
}

void profile() {
#ifdef DEBUG
  printf("Debug mode must be disabled!\n");
  return;
#endif
  printf("Profiling communication performance...\n");
  printf("Latency: %f us\n", measure_ping_us());
  printf("Throughput: %f mbps\n", measure_throughput_mbps());
}

int main() {
  info = carp_connect();
  carp_reset();
  profile();
  carp_disconnect();
  return 0;
}
