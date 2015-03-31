#include "testframework.cinclude"

void test() {
  printf("Test: Counters\n");

  int n = 5;

  write_state(0,1,1, 1);

  store(0);
    counter_reset(0);
    read_state(0,1,1);
    counter_increment(0);
    jump_equal(10, 0, n);
    jump(1);
  end();

  store(10);
    break_out();
  end();

  jump(0);

  for (int i = 0; i < n; i++) {
    assert_uint32(1, get_state());
  }
}
