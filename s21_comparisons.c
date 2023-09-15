#include "s21_decimal.h"

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int sign1 = (d1.bits[3] & sign_mask), sign2 = (d2.bits[3] & sign_mask);
  int scale1 = s21_get_scale(&d1), scale2 = s21_get_scale(&d2);

  s21_decimal cur1, cur2;

  s21_init_decimal(&cur1);
  s21_init_decimal(&cur2);
  s21_copy_decimal(d1, &cur1);
  s21_copy_decimal(d2, &cur2);

  int mx = s21_max(scale1, scale2);
  while (scale1 < mx) {
    s21_sub10(&cur1, &cur1);
    scale1++;
  }

  while (scale2 < mx) {
    s21_sub10(&cur2, &cur2);
    scale2++;
  }

  cur1.bits[3] = (sign1 & sign_mask) + (mx << 16);
  cur2.bits[3] = (sign2 & sign_mask) + (mx << 16);

  int ans = 1;

  bool f1 = (cur1.bits[0] || cur1.bits[1] || cur1.bits[2]);
  bool f2 = (cur2.bits[0] || cur2.bits[1] || cur2.bits[2]);

  if (f1 || f2) {
    for (int i = 0; i < 4; ++i) {
      if (cur1.bits[i] != cur2.bits[i]) {
        ans = 0;
        break;
      }
    }
  }
  return ans;
}

int s21_check_le_without_sign(s21_decimal d1, s21_decimal d2, int *isEqual) {
  int ans = 0;
  for (int i = 2; i >= 0; --i) {
    if (d1.bits[i] == d2.bits[i]) {
      *isEqual = 1;
    } else {
      *isEqual = 0;
      if ((ui)d1.bits[i] < (ui)d2.bits[i]) ans = 1;
      break;
    }
  }
  return ans;
}

int s21_check_le_with_sign(s21_decimal d1, s21_decimal d2, int sign1,
                           int sign2) {
  int ans = 0;
  if (sign1 && !sign2) {
    bool st1 = (d1.bits[0] || d1.bits[1] || d1.bits[2]);
    bool st2 = (d2.bits[0] || d2.bits[1] || d2.bits[2]);
    if (st1 || st2) ans = 1;
  } else if (sign1 == sign2) {
    int isEqual = 0, st = s21_check_le_without_sign(d1, d2, &isEqual);
    bool f1 = (!st && sign1 && !isEqual);
    bool f2 = (st && !sign1 && !isEqual);
    if (f1 || f2) ans = 1;
  }
  return ans;
}

int s21_is_less_not_equal(s21_decimal d1, s21_decimal d2) {
  int ans = 0;
  int sign1 = (d1.bits[3] & sign_mask), sign2 = (d2.bits[3] & sign_mask);
  int scale1 = s21_get_scale(&d1), scale2 = s21_get_scale(&d2);

  s21_decimal cur1, cur2;

  s21_init_decimal(&cur1);
  s21_init_decimal(&cur2);
  s21_copy_decimal(d1, &cur1);
  s21_copy_decimal(d2, &cur2);

  int mx = s21_max(scale1, scale2);
  while (scale1 < mx) {
    s21_sub10(&cur1, &cur1);
    scale1++;
  }

  while (scale2 < mx) {
    s21_sub10(&cur2, &cur2);
    scale2++;
  }

  scale1 = s21_get_scale(&d1);
  scale2 = s21_get_scale(&d2);

  cur1.bits[3] = (sign1 & sign_mask) + (scale1 << 16);
  cur2.bits[3] = (sign2 & sign_mask) + (scale2 << 16);

  ans = s21_check_le_with_sign(cur1, cur2, sign1, sign2);

  return ans;
}

int s21_is_less(s21_decimal d1, s21_decimal d2) {
  bool isEqual = true;
  for (int i = 0; (i < 3 && isEqual); ++i) {
    if ((ui)d1.bits[i] != (ui)d2.bits[i]) isEqual = false;
  }
  bool status = true;
  bool st1 = (d1.bits[0] || d1.bits[1] || d1.bits[2]);
  bool st2 = (d2.bits[0] || d2.bits[1] || d2.bits[2]);
  if (st1 || st2) status = false;
  int ans = 0;
  if (isEqual && !status) {
    int scale1 = s21_get_scale(&d1), scale2 = s21_get_scale(&d2);
    int sign1 = ((d1.bits[3] & sign_mask) >> 31),
        sign2 = ((d2.bits[3] & sign_mask) >> 31);
    if (sign1 == sign2) {
      if (scale1 != scale2) {
        bool f1 = ((scale1 > scale2) && !sign1);
        bool f2 = ((scale1 < scale2) && sign1);
        if (f1 || f2) ans = 1;
      }
    } else if (sign1 && !sign2 && !status) {
      ans = 1;
    }
  } else {
    ans = s21_is_less_not_equal(d1, d2);
  }
  return ans;
}

int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_is_less(d1, d2) || s21_is_equal(d1, d2));
}

int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  return !s21_is_less_or_equal(d1, d2);
}

int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return (!s21_is_less_or_equal(d1, d2) || s21_is_equal(d1, d2));
}

int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return !s21_is_equal(d1, d2);
}
