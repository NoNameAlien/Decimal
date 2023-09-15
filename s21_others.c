#include "s21_decimal.h"

int s21_truncate(s21_decimal d, s21_decimal *ans) {
  s21_init_decimal(ans);
  int scale = s21_get_scale(&d);
  for (int i = 0; i < 3; ++i) ans->bits[i] = d.bits[i];
  ans->bits[3] = (d.bits[3] & sign_mask);
  while (scale != 0) {
    s21_div10(ans, ans);
    --scale;
  }
  return 0;
}

int s21_round(s21_decimal d, s21_decimal *ans) {
  s21_init_decimal(ans);
  int scale = s21_get_scale(&d);
  for (int i = 0; i < 3; ++i) ans->bits[i] = d.bits[i];
  ans->bits[3] = (d.bits[3] & sign_mask);
  int ost = 0;
  while (scale != 0) {
    ost = s21_div10(ans, ans);
    --scale;
  }
  if (ost >= 5) (ans->bits[0])++;
  return 0;
}

int s21_floor(s21_decimal d, s21_decimal *ans) {
  s21_init_decimal(ans);
  s21_truncate(d, ans);
  int scale = s21_get_scale(&d);
  bool flag = false;
  for (int i = 0; i < 3; ++i) {
    if (d.bits[i] != 0) flag = true;
  }
  if ((d.bits[3] & sign_mask) && scale && flag) (ans->bits[0])++;
  return 0;
}

int s21_negate(s21_decimal d, s21_decimal *ans) {
  s21_init_decimal(ans);
  for (int i = 0; i < 4; ++i) ans->bits[i] = d.bits[i];
  if (d.bits[3] & sign_mask) {
    s21_bit_set(ans, 127, 0);
  } else {
    s21_bit_set(ans, 127, 1);
  }
  return 0;
}