#include "testframework.cinclude"

void test() {
  printf("Test: Counters\n");
  printf("Instructions: store, end, jump, break, write_state read_state\n");
  printf("\n");

  int n = 5;

  write_state(1,1,0, 1);

  store(0);
    counter_reset(0);
    read_state(1,1,0);
    counter_increment(0);
    jump_equal(10, 0, n);
    jump(1);
  end();

  store(10);
    break_out();
  end();

  jump(n);

  for (int i = 0; i < n; i++) {
    assert_uint32(1, get_state());
  }
}
