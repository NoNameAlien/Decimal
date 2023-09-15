#include "s21_decimal.h"

int s21_from_int_to_decimal(int x, s21_decimal *d) {
  int flag = 1;
  s21_init_decimal(d);
  if (d) {
    flag = 0;
    if (x < 0) {
      d->bits[3] = x & sign_mask;
      x *= -1;
    }
    d->bits[0] = x;
  }
  return flag;
}

int s21_from_decimal_to_int(s21_decimal d, int *x) {
  int flag = 1;
  s21_truncate(d, &d);
  if (!d.bits[2] && !d.bits[1] && !(d.bits[0] & sign_mask)) {
    flag = 0;
    *x = d.bits[0];
    *x *= ((d.bits[3] & sign_mask) ? -1 : 1);
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal d, float *x) {
  int flag = 1, sign = (d.bits[3] & sign_mask), scale = s21_get_scale(&d);
  double res = 0;
  if (x) {
    for (int i = 95; i >= 0; --i) {
      if (s21_get_bit(&d, i)) res += pow(2, i);
    }
    while (scale) {
      res /= 10.0;
      --scale;
    }
    *x = (float)res;
    if (sign) (*x) *= -1;
    flag = 0;
  }
  return flag;
}

int s21_from_float_to_decimal(float x, s21_decimal *d) {
  int status = 0;
  if (d) {
    s21_init_decimal(d);
    float f_abs = (x > 0 ? x : -x);
    if (f_abs > (float)7.922816e28) {
      status = 1;
    } else if (f_abs < (float)0.5e-28) {
      s21_init_decimal(d);
    } else {
      int shift_exp = -6;
      char str[16] = {0};
      sprintf(str, "%.6e", f_abs);

      int exp = shift_exp;

      int tmpexp = 10 * (str[10] - '0') + (str[11] - '0');
      if (str[9] == '-') tmpexp *= (-1);
      exp += tmpexp;

      d->bits[0] = get_float_mantiss_from_str(str);

      // if (exp < -28) {
      //   // int mid = 5, cnt = -(28 + exp);
      //   // for (int i = 0; i < cnt - 1; ++i) s21_div10(d, d);
      //   // int res = get_last_digit(d);
      //   // s21_div10(d, d);
      //   // if (res > mid) incr_mant(d);
      //   // exp = -28;
      // } else {
      //   s21_decimal tmp = *d;
      //   while (exp > 0 && !status) {
      //     status = s21_mul10(&tmp);
      //     if (!status) s21_mul10(d);
      //     --exp;
      //   }
      // }
      exp *= -1;
      set_exponent((ui)exp, d);
      s21_bit_set(d, 127, (x < 0));
      s21_norm(d);
    }
  } else {
    status = 1;
  }
  return status;
}