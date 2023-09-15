#include "s21_decimal.h"

void print_decimal(s21_decimal d) {
  for (int i = 3; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", (d.bits[i] >> j) & 1);
    }
    printf(" ");
  }
  printf("\n");
}

int main() {
  s21_decimal var_a = {{1, 0, 0, 0}};
  // var: 1
  s21_decimal var_b = {{10, 0, 0, 65536}};
  // var: 1,0
  int return_res = s21_is_equal(var_a, var_b);

  printf("%d %d %d %d\n", var_a.bits[3], var_a.bits[2], var_a.bits[1],
         var_a.bits[0]);
  printf("%d %d %d %d\n", var_b.bits[3], var_b.bits[2], var_b.bits[1],
         var_b.bits[0]);

  printf("%d", return_res);

  return 0;
}
