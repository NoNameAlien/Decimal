#include "s21_decimal.h"

int s21_max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

void clear_exp(s21_decimal *number) {
  number->bits[3] &= sign_mask;
  return;
}

void s21_init_decimal(s21_decimal *d) {
  for (int i = 0; i < 4; ++i) d->bits[i] = 0;
}

void s21_copy_decimal(s21_decimal need_copy, s21_decimal *d) {
  for (int i = 0; i < 4; ++i) d->bits[i] = need_copy.bits[i];
}

void s21_bit_set(s21_decimal *d, int bit, int need_bit) {
  int id = bit / 32;
  if (!need_bit) {
    d->bits[id] = ((d->bits[id]) & ~(1 << (bit % 32)));
  } else {
    d->bits[id] = ((d->bits[id]) | (1 << (bit % 32)));
  }
}

int get_float_mantiss_from_str(char *str) {
  int result = (*str - '0');
  str += 2;
  while ((*str) != 'e') {
    result = (10 * result) + (*str - '0');
    ++str;
  }
  return result;
}

void set_exponent(ui exp, s21_decimal *number) {
  if (exp <= 28) {
    clear_exp(number);
    exp <<= 16;
    number->bits[3] |= exp;
  }
  return;
}

int s21_get_bit(s21_decimal *d, int bit) {
  int ans = 0;
  if (((d->bits[bit / 32]) & (1 << bit % 32)) != 0) ans = 1;
  return ans;
}

int s21_div10(s21_decimal *d, s21_decimal *ans) {
  ull buffer, div_buffer;
  ui mod, res;
  buffer = div_buffer = mod = res = 0;
  for (int i = 2; i >= 0; --i) {
    res = (ui)(d->bits[i]);
    mod = (buffer + res) % 10;
    div_buffer = (buffer + res) / 10;
    ans->bits[i] = (ui)div_buffer;
    buffer = mod;
    buffer <<= 32;
  }
  return mod;
}

void s21_shift(s21_decimal *value) {
  for (int i = 95; i > 0; --i) {
    if (s21_get_bit(value, i - 1) == 1) {
      s21_bit_set(value, i, 1);
    } else {
      s21_bit_set(value, i, 0);
    }
  }
  s21_bit_set(value, 0, 0);
}

int s21_get_scale(s21_decimal *d) {
  s21_decimal res;
  s21_init_decimal(&res);
  res.bits[3] = (d->bits[3]);
  res.bits[3] = ((res.bits[3] << 8) >> 24);
  return res.bits[3];
}

int s21_simple_add(s21_decimal d1, s21_decimal d2, s21_decimal *result) {
  int d1_bit, d2_bit;
  int sub_result_bit = 0;
  s21_init_decimal(result);
  for (int i = 0; i < 96; ++i) {
    d1_bit = s21_get_bit(&d1, i);
    d2_bit = s21_get_bit(&d2, i);
    s21_bit_set(result, i, d1_bit ^ d2_bit ^ sub_result_bit);
    sub_result_bit = (d1_bit && d2_bit) || (d1_bit && sub_result_bit) ||
                     (d2_bit && sub_result_bit);
  }
  return sub_result_bit;
}

void s21_sub10(s21_decimal *d, s21_decimal *res) {
  s21_decimal buf1, buf2;
  s21_init_decimal(&buf1);
  s21_init_decimal(&buf2);
  for (int i = 0; i < 3; i++) {
    buf1.bits[i] = d->bits[i];
    buf2.bits[i] = d->bits[i];
  }
  for (int i = 0; i < 1; ++i) s21_shift(&buf1);
  for (int i = 0; i < 3; ++i) s21_shift(&buf2);
  s21_simple_add(buf1, buf2, res);
}

ui get_exponent(const s21_decimal *d) {
  ui notSignMask = ~(0x80000000);
  int exp = (d->bits[3] & notSignMask);
  return exp >>= 16;
}

void s21_norm(s21_decimal *d) {
  s21_decimal tmp = (*d);
  int tmp_exp = get_exponent(&tmp);
  while ((tmp_exp > 0) && (0 == s21_div10(&tmp, &tmp))) {
    s21_div10(d, d);
    --tmp_exp;
  }
  set_exponent((ui)(tmp_exp), d);
  return;
}

/// Algorithm functions

void set_exp(ui *dec, uc exp) { *dec = exp << 16; }

void set_bit(ui *num, uc bit_num) { *num |= (uc)1 << bit_num; }

void reset_bit(ui *num, uc bit_num) { *num &= ~((uc)1 << bit_num); }

char get_exp(ui dec) {
  ui exp = 0;
  for (uc i = 16; i < 24; i++) {
    if (dec & (uc)1 << i) {
      set_bit(&exp, i - 16);
    }
  }
  return exp;
}

char check_bit(ui num, uc index) {
  char bit = 0;
  if (index < 32) {
    if ((num & (ui)1 << index) != 0) {
      bit = 1;
    } else {
      bit = 0;
    }
  } else {
    bit = -1;
  }
  return bit;
}

uc rand_exp() { return rand() % 29; }

uc rand_sign() { return (rand() % 11) > 5 ? 1 : 0; }

char get_sign(ui dec) { return check_bit(dec, 31); }

void set_sign(ui *dec, char sign) {
  sign ? set_bit(dec, 31) : reset_bit(dec, 31);
}

/// @brief Перевод в bdecimal
/// @param dec
/// @return big_dec
bdecimal decimal_to_bdecimal(s21_decimal dec) {
  bdecimal big_dec = {0};
  big_dec.bits[0] = dec.bits[0];
  big_dec.bits[1] = dec.bits[1];
  big_dec.bits[2] = dec.bits[2];
  big_dec.mantice = dec.bits[3];
  return big_dec;
}

s21_decimal set_rand_decimal() {
  s21_decimal dec = {0};
  dec.bits[0] = rand();
  dec.bits[1] = rand();
  dec.bits[2] = rand();
  set_exp(&dec.bits[3], rand_exp());
  set_sign(&dec.bits[3], rand_sign());
  return dec;
}

s21_decimal set_decimal(ui low_bit, ui mid_bit, ui high_bit, uc exp, uc sign) {
  s21_decimal dec = {0};
  dec.bits[0] = low_bit;
  dec.bits[1] = mid_bit;
  dec.bits[2] = high_bit;
  set_exp(&dec.bits[3], exp);
  set_sign(&dec.bits[3], sign);
  return dec;
}

void shift_bdecimal_to_high(bdecimal *bdec) {
  for (char i = 5; i >= 0; i--) {
    if (check_bit(bdec->bits[(uc)i], 31)) {
      set_bit(&(bdec->bits[(uc)i + 1]), 0);
    }
    bdec->bits[(uc)i] = singl_high_shift(bdec->bits[(uc)i]);
  }
}

ui singl_high_shift(ui num) { return num <<= 1; }

ui singl_low_shift(ui num) { return num >>= 1; }

uc is_empty_bdecimal(bdecimal bdec) {
  return bdec.bits[5] || bdec.bits[4] || bdec.bits[3] || bdec.bits[2] ||
                 bdec.bits[1] || bdec.bits[0]
             ? 0
             : 1;
}

int is_empty_dec(s21_decimal dec) {
  return dec.bits[2] || dec.bits[1] || dec.bits[0] ? 0 : 1;
}

uc shift_bdecimal_to_low(bdecimal *bdec) {
  uc was_shifted = 0;
  if (!is_empty_bdecimal(*bdec)) {
    for (char i = 0; i < 6; i++) {
      bdec->bits[(uc)i] = singl_low_shift(bdec->bits[(uc)i]);
      if (check_bit(bdec->bits[(uc)i + 1], 0)) {
        set_bit(&(bdec->bits[(uc)i]), 31);
      }
      was_shifted = 1;
    }
  }

  return was_shifted;
}

char *print_dec(s21_decimal dec) {
  char *str = calloc(256, sizeof(char));
  sprintf(str, "%hhd %hhu %u %u %u\n", get_sign(dec.bits[3]),
          get_exp(dec.bits[3]), dec.bits[2], dec.bits[1], dec.bits[0]);
  return str;
}

/// @brief Исключающее ИЛИ
/// @param value_1
/// @param value_2
/// @return bdecimal
bdecimal exclusive_or(bdecimal value_1, bdecimal value_2) {
  for (int i = 0; i < INT_BIG_DECIMAL; i++) {
    value_1.bits[i] = value_1.bits[i] ^ value_2.bits[i];
  }

  return value_1;
}

/// @brief Логическое И
/// @param value_1
/// @param value_2
/// @return bdecimal
bdecimal bit_and(bdecimal value_1, bdecimal value_2) {
  bdecimal result_bdec = {0};
  for (int i = 0; i < INT_BIG_DECIMAL; i++) {
    result_bdec.bits[i] = value_1.bits[i] & value_2.bits[i];
  }
  return result_bdec;
}

bdecimal negative(bdecimal value_1) {
  for (int i = 0; i < INT_BIG_DECIMAL; i++) {
    value_1.bits[i] = ~value_1.bits[i];
  }
  bdecimal value_2 = {0};
  value_2.bits[0] = 1;

  value_1 = simple_add(value_1, value_2);

  return value_1;
}

bdecimal simple_add(bdecimal value_1, bdecimal value_2) {
  bdecimal result_bdec = {0};

  result_bdec = exclusive_or(value_1, value_2);
  value_1 = bit_and(value_1, value_2);
  shift_bdecimal_to_high(&value_1);

  while (DEC1_ZERO) {
    value_2 = result_bdec;
    result_bdec = exclusive_or(result_bdec, value_1);
    value_1 = bit_and(value_2, value_1);
    shift_bdecimal_to_high(&value_1);
  }

  return result_bdec;
}

/// @brief Сложение bdecimal
/// @param value_1
/// @param value_2
/// @param *result_bdec
void full_add(bdecimal value_1, bdecimal value_2, bdecimal *result_bdec) {
  uc sign1 = get_sign(value_1.mantice);
  uc sign2 = get_sign(value_2.mantice);

  set_sign(&value_1.mantice, 0);
  set_sign(&value_2.mantice, 0);

  if (sign1 ^ sign2) {
    if (bdecimal_is_less(value_1, value_2))
      *result_bdec = simple_sub(value_2, value_1);
    else
      *result_bdec = simple_sub(value_1, value_2);
  } else {
    *result_bdec = simple_add(value_1, value_2);
  }

  if (bdecimal_is_less(value_1, value_2) && sign2) {
    set_sign(&result_bdec->mantice, 1);
  } else if (bdecimal_is_less(value_2, value_1) && sign1) {
    set_sign(&result_bdec->mantice, 1);
  }
}

bdecimal simple_sub(bdecimal value_1, bdecimal value_2) {
  bdecimal result_bdec = {0};
  result_bdec = simple_add(value_1, negative(value_2));
  reset_bit(&result_bdec.bits[5], 31);
  return result_bdec;
}

/// @brief Вычитание bdecimal
/// @param value_1
/// @param value_2
/// @param *result_bdec
void full_sub(bdecimal value_1, bdecimal value_2, bdecimal *result_bdec) {
  uc sign1 = get_sign(value_1.mantice);
  uc sign2 = get_sign(value_2.mantice);

  set_sign(&value_1.mantice, 0);
  set_sign(&value_2.mantice, 0);

  if (sign1 ^ sign2) {
    *result_bdec = simple_add(value_1, value_2);
  } else {
    if (bdecimal_is_less(value_1, value_2))
      *result_bdec = simple_sub(value_2, value_1);
    else
      *result_bdec = simple_sub(value_1, value_2);
  }

  if (bdecimal_is_less(value_1, value_2)) {
    if (sign2)
      set_sign(&result_bdec->mantice, 0);
    else
      set_sign(&result_bdec->mantice, 1);
  } else if (bdecimal_is_less(value_2, value_1)) {
    if (sign1)
      set_sign(&result_bdec->mantice, 1);
    else
      set_sign(&result_bdec->mantice, 0);
  }
}

/// @brief Умножение bdecimal
/// @param value_1
/// @param value_2
/// @return result_bdec
bdecimal simple_mul(bdecimal value_1, bdecimal value_2) {
  bdecimal result_bdec = {0};
  while (DEC2_ZERO) {
    if ((value_2.bits[0] & 0x1) == 0x1)
      result_bdec = simple_add(value_1, result_bdec);

    shift_bdecimal_to_low(&value_2);
    shift_bdecimal_to_high(&value_1);
  }

  set_sign(&result_bdec.mantice, sign_def(value_1, value_2));
  return result_bdec;
}

/// @brief Деление bdecimal
/// @param value_1
/// @param value_2
/// @return rez
bdecimal simple_div(bdecimal value_1, bdecimal value_2) {
  bdecimal temp_big_1 = {0};
  temp_big_1 = value_1;

  bdecimal rez_exp = {0};
  bdecimal rez = {0};

  while (bdecimal_is_to_equals(temp_big_1, value_2)) {
    bdecimal temp_divider = {0};
    temp_divider = value_2;
    uc ten_exp = 0;
    ten_exp = mul_to_exp(temp_big_1, &temp_divider);
    bdecimal bten_exp = {0};
    bten_exp.bits[0] = 1;

    for (uc i = 0; i < ten_exp - 1; i++) {
      bten_exp = simple_mul(bten_exp, bdec_ten);
    }

    uc sum_to_div = 0;
    sum_to_div = sum_to_divided(&temp_big_1, &temp_divider);

    bdecimal bsum_div = {0};
    bsum_div.bits[0] = sum_to_div;
    rez_exp = simple_mul(bten_exp, bsum_div);

    rez = simple_add(rez, rez_exp);
  }
  return rez;
}

/// @brief Деление bdecimal
/// @param value_1
/// @param value_2
/// @return result_bdec
bdecimal full_div(bdecimal value_1, bdecimal value_2) {
  bdecimal result_bdec = {0};
  bdecimal big_rezult_mod = {0};
  bdecimal one = {0};
  one.bits[0] = 1;

  result_bdec = simple_div(value_1, value_2);
  big_rezult_mod = simple_mod(value_1, value_2);

  uc mul = 30 - mul_to_exp(result_bdec, &one);
  if (mul == 30) mul--;

  uc exp = 0;

  while (big_rezult_mod.bits[0] != 0 && mul != 0) {
    mul--;
    exp++;

    value_1 = simple_mul(big_rezult_mod, bdec_ten);
    result_bdec = simple_mul(result_bdec, bdec_ten);
    result_bdec = simple_add(result_bdec, simple_div(value_1, value_2));
    big_rezult_mod = simple_mod(value_1, value_2);
  }

  set_exp(&result_bdec.mantice, exp);

  set_sign(&result_bdec.mantice, sign_def(value_1, value_2));
  return result_bdec;
}

uc sign_def(bdecimal value_1, bdecimal value_2) {
  return (get_sign(value_1.mantice) ^ get_sign(value_2.mantice));
}

bdecimal simple_mod(bdecimal value_1, bdecimal value_2) {
  bdecimal result_bdec = {0};
  bdecimal mod = {0};

  mod = simple_div(value_1, value_2);

  bdecimal mul_tmp = {0};
  mul_tmp = simple_mul(mod, value_2);
  result_bdec = simple_sub(value_1, mul_tmp);

  return result_bdec;
}

uc sum_to_divided(bdecimal *temp_big_1, bdecimal *temp_divider) {
  uc count_sub = 0;
  while (bdecimal_is_to_equals(*temp_big_1, *temp_divider)) {
    *temp_big_1 = simple_sub(*temp_big_1, *temp_divider);
    count_sub++;
  }
  return count_sub;
}

uc mul_to_exp(bdecimal temp_big_1, bdecimal *temp_divider) {
  set_sign(&temp_big_1.mantice, 0);
  uc ten_exp = 0;

  bdecimal divider = {0};
  char was_in_if = 0;

  if (bdecimal_is_to_equals(temp_big_1, simple_mul(*temp_divider, bdec_ten))) {
    while (bdecimal_is_to_equals(temp_big_1, *temp_divider)) {
      ten_exp++;
      *temp_divider = simple_mul(*temp_divider, bdec_ten);
      if (bdecimal_is_to_equals(temp_big_1, *temp_divider)) {
        was_in_if = 1;
        divider = *temp_divider;
      }
    }
    if (was_in_if) {
      *temp_divider = divider;
    }
  }
  return ten_exp;
}

// simple arithmetic

/// @brief Приведение к точке
/// @param *value_1
/// @param *value_2
void normalize_bdecimal(bdecimal *value_1, bdecimal *value_2) {
  if (get_exp(value_1->mantice) > get_exp(value_2->mantice)) {
    cast_by_exp(value_2, get_exp(value_1->mantice));
  } else {
    cast_by_exp(value_1, get_exp(value_2->mantice));
  }
}

void cast_by_exp(bdecimal *bdec, uc exp) {
  uc sign = 0;
  sign = get_sign(bdec->mantice);
  for (; exp > get_exp(bdec->mantice);) {
    *bdec = simple_mul(*bdec, bdec_ten);
    set_exp(&bdec->mantice, get_exp(bdec->mantice) + 1);
    set_sign(&bdec->mantice, sign);
  }
}

/// @brief Перевод обратно в decimal
/// @param *bdec
/// @param *dec_rez
/// @result owerflow
int bdecimal_to_decimal(bdecimal *bdec, s21_decimal *dec_rez) {
  int exp = get_exp(bdec->mantice);
  int sign = 0;
  int overflow = 0;
  sign = get_sign(bdec->mantice);

  // round fract part
  bdecimal bdec_rounded = {0};
  // round fract part
  while (is_big_converted_to_dec(*bdec)) {
    if (!get_exp(bdec->mantice)) {
      overflow = 1;
      break;
    }

    // round fract part
    if (!check_high_ints_big(simple_div(*bdec, bdec_ten))) {
      bdec_rounded = *bdec;
    }

    *bdec = simple_div(*bdec, bdec_ten);
    set_exp(&bdec->mantice, --exp);
    set_sign(&bdec->mantice, sign);
  }

  if (!overflow) {
    // round fract part
    int fract_part = get_big_fract_part(bdec_rounded);
    int first_int_part = get_big_fract_part(*bdec);
    overflow = round_bdecimal(bdec, fract_part, first_int_part);
    // round fract part

    fill_dec_from_big(*bdec, dec_rez);
  }

  return overflow;
}

uc round_bdecimal(bdecimal *bdec_rounded, int fract_part, int int_part) {
  uc exp = get_exp(bdec_rounded->mantice);
  uc sign = get_sign(bdec_rounded->mantice);

  int was_rounded = 0;
  if (get_exp(bdec_rounded->mantice) < 28) {
    if (fract_part > 4) {
      *bdec_rounded = simple_add(*bdec_rounded, bdec_one);
      was_rounded = 1;
    }
    if (int_part == 9 && was_rounded) {
      *bdec_rounded = simple_div(*bdec_rounded, bdec_ten);
      set_exp(&bdec_rounded->mantice, --exp);
      set_sign(&bdec_rounded->mantice, sign);
    }

  } else {
    if ((fract_part > 5) || ((fract_part == 5) && (int_part % 2 == 0))) {
      *bdec_rounded = simple_add(*bdec_rounded, bdec_one);
      was_rounded = 1;
    }
    if (int_part == 9 && was_rounded) {
      *bdec_rounded = simple_div(*bdec_rounded, bdec_ten);
      set_exp(&bdec_rounded->mantice, --exp);
      set_sign(&bdec_rounded->mantice, sign);
    }
    if ((fract_part == 0 || int_part == 0) && !was_rounded) {
      *bdec_rounded = simple_div(*bdec_rounded, bdec_ten);
      set_exp(&bdec_rounded->mantice, --exp);
      set_sign(&bdec_rounded->mantice, sign);
    }
  }

  return 0;
}

uc get_big_fract_part(bdecimal bdec) {
  bdecimal bdec_fract = simple_mod(bdec, bdec_ten);
  return (uc)bdec_fract.bits[0];
}

void fill_dec_from_big(bdecimal bdec, s21_decimal *dec) {
  if (!is_empty_bdecimal(bdec)) {
    dec->bits[0] = bdec.bits[0];
    dec->bits[1] = bdec.bits[1];
    dec->bits[2] = bdec.bits[2];
    dec->bits[3] = bdec.mantice;
  }
}

uc is_big_converted_to_dec(bdecimal bdec) {
  return check_high_ints_big(bdec) || get_exp(bdec.mantice) > 28;
}

uc check_high_ints_big(bdecimal bdec) {
  return (bdec.bits[5] || bdec.bits[4] || bdec.bits[3]) ? 1 : 0;
}

// for comparison
// big_dec1 < big_dec2, 0 - false, 1 - true
int bdecimal_is_less(bdecimal value_1, bdecimal value_2) {
  if (get_sign(value_1.mantice) == 1 && get_sign(value_2.mantice) == 0) {
    return 1;  //
  }
  if (get_sign(value_1.mantice) == 0 && get_sign(value_2.mantice) == 1) {
    return 0;  //
  }

  for (int i = 5; i >= 0; i--) {
    if (value_1.bits[i] == value_2.bits[i]) {
      continue;
    }

    if (value_1.bits[i] < value_2.bits[i]) {
      if (get_sign(value_1.mantice) == 0) {
        return 1;
      } else {
        return 0;
      }
    } else {
      if (get_sign(value_1.mantice) == 0) {
        return 0;
      } else {
        return 1;
      }
    }
  }
  return 0;
}

// // big_dec1 = big_dec2, 0 - false, 1 - true
// int bdecimal_is_equal(bdecimal value_1, bdecimal value_2) {
//   int count = 0;
//   if (get_sign(value_1.mantice) == get_sign(value_2.mantice)) {
//     for (int i = 5; i >= 0; i--) {
//       if (value_1.bits[i] == value_2.bits[i]) {
//         count++;
//       }
//     }
//   }
//   return (count == 6) ? 1 : 0;
// }

// // big_dec1 > big_dec2, 0 - false, 1 - true
// int bdecimal_is_greater(bdecimal value_1, bdecimal value_2) {
//   return (bdecimal_is_less(value_1, value_2) == 0 &&
//           bdecimal_is_equal(value_1, value_2) == 0)
//              ? 1
//              : 0;
// }

// int bdecimal_is_greater_or_equal(bdecimal value_1, bdecimal value_2) {
//   return (bdecimal_is_less(value_1, value_2) == 1) ? 0 : 1;
// }

// // big_dec1 != big_dec2, 0 - false, 1 - true
// int bdecimal_is_not_equal(bdecimal value_1, bdecimal value_2) {
//   return (bdecimal_is_equal(value_1, value_2) ? 0 : 1);
// }

// // big_dec1 <= big_dec2, 0 - false, 1 - true
// int bdecimal_is_less_or_equal(bdecimal value_1, bdecimal value_2) {
//   return (bdecimal_is_greater(value_1, value_2) == 1) ? 0 : 1;
// }

// comparison

// compare
int bdecimal_is_to_equals(bdecimal value_1, bdecimal value_2) {
  for (int i = INT_BIG_DECIMAL - 1; i >= 0; i--) {
    if (value_1.bits[i] == 0 && value_2.bits[i] == 0) {
      continue;
    }
    if (value_1.bits[i] > value_2.bits[i]) {
      return 1;
    }
    if (value_1.bits[i] < value_2.bits[i]) {
      return 0;
    }
    if (value_1.bits[i] == value_2.bits[i]) {
      if (i == 0) return 1;
      continue;
    }
  }
  return 0;
}
