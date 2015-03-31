#include "testframework.cinclude"

void test() {
  printf("Test: Instruction storage\n");

  int n = 4;

  write_state(0,1,1, 1);

  store(0);
    read_state(0,1,1);
    break_out();
  end();

  for (int i = 0; i < n; i++) {
    jump(0);
    assert_uint32(1, get_state());
  }
}
