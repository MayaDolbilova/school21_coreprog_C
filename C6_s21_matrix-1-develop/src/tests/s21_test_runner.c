#include "s21_matrix_tests.h"

int main() {
  int no_failed = 0;

  no_failed |= matrix_tests();

  return (no_failed == 0) ? 0 : 1;
}
