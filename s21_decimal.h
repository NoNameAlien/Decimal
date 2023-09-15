#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define sign_mask 0x80000000

#define INT_DECIMAL 3
#define INT_BIG_DECIMAL 6
#define SO_BIG_NUMBER 79228162514264337593543950335
#define SO_SMALL_NUMBER 1e-28

#define DEC1_ZERO                                                              \
  (value_1.bits[0] || value_1.bits[1] || value_1.bits[2] || value_1.bits[3] || \
   value_1.bits[4] || value_1.bits[5])
#define DEC2_ZERO                                                              \
  (value_2.bits[0] || value_2.bits[1] || value_2.bits[2] || value_2.bits[3] || \
   value_2.bits[4] || value_2.bits[5])

typedef unsigned int ui;
typedef unsigned char uc;
typedef unsigned long long ull;

typedef enum bool { false, true } bool;
typedef enum digits { LOW, MID, HIGH, SCALE } digits;
typedef enum errors { OK, INF, NEGINF, DIV_0 } errors;
typedef enum sings { POSITIVE, NEGATIVE } sings;

typedef struct {
  ui bits[4];
} s21_decimal;

typedef struct {
  union {
    ui bits[6];
  };
  ui mantice;

} bdecimal;

static const bdecimal bdec_ten = {.mantice = 0,
                                  .bits[5] = 0,
                                  .bits[4] = 0,
                                  .bits[3] = 0,
                                  .bits[2] = 0,
                                  .bits[1] = 0,
                                  .bits[0] = 10};

static const bdecimal bdec_one = {.mantice = 0,
                                  .bits[5] = 0,
                                  .bits[4] = 0,
                                  .bits[3] = 0,
                                  .bits[2] = 0,
                                  .bits[1] = 0,
                                  .bits[0] = 1};

static const bdecimal bdec_null = {.mantice = 0,
                                   .bits[5] = 0,
                                   .bits[4] = 0,
                                   .bits[3] = 0,
                                   .bits[2] = 0,
                                   .bits[1] = 0,
                                   .bits[0] = 0};

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_max(int a, int b);
void clear_exp(s21_decimal *number);

int s21_comparison_equal(s21_decimal tmp_1, s21_decimal tmp_2);

void s21_init_decimal(s21_decimal *d);
void s21_copy_decimal(s21_decimal need_copy, s21_decimal *d);

void s21_bit_set(s21_decimal *d, int bit, int need_bit);
void set_exponent(ui exp, s21_decimal *number);
int s21_get_bit(s21_decimal *d, int bit);
int get_float_mantiss_from_str(char *str);
int get_last_digit(s21_decimal *number);

int incr_mant(s21_decimal *value);
int s21_mul10(s21_decimal *value);
int s21_div10(s21_decimal *d, s21_decimal *ans);
int s21_get_scale(s21_decimal *d);
int s21_simple_add(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
void s21_sub10(s21_decimal *d, s21_decimal *res);
ui get_exponent(const s21_decimal *d);
void s21_norm(s21_decimal *d);

int s21_truncate(s21_decimal d, s21_decimal *ans);
int s21_round(s21_decimal d, s21_decimal *ans);
int s21_floor(s21_decimal d, s21_decimal *ans);
int s21_negate(s21_decimal d, s21_decimal *ans);

int s21_from_int_to_decimal(int x, s21_decimal *d);
int s21_from_decimal_to_int(s21_decimal d, int *x);
int s21_from_decimal_to_float(s21_decimal d, float *x);
int s21_from_float_to_decimal(float x, s21_decimal *d);

int s21_is_equal(s21_decimal d1, s21_decimal d2);
int s21_check_le_without_sign(s21_decimal d1, s21_decimal d2, int *isEqual);
int s21_check_le_with_sign(s21_decimal d1, s21_decimal d2, int sign1,
                           int sign2);
int s21_is_less_not_equal(s21_decimal d1, s21_decimal d2);
int s21_is_less(s21_decimal d1, s21_decimal d2);
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_greater(s21_decimal d1, s21_decimal d2);
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_not_equal(s21_decimal d1, s21_decimal d2);

void set_exp(ui *dec, uc exp);
void set_bit(ui *num, uc bit_num);
void reset_bit(ui *num, uc bit_num);
char get_exp(ui dec);
char check_bit(ui num, uc index);
uc rand_exp();
uc rand_sign();
char get_sign(ui dec);
void set_sign(ui *dec, char sign);
bdecimal decimal_to_bdecimal(s21_decimal dec);
s21_decimal set_rand_decimal();
s21_decimal set_decimal(ui low_bit, ui mid_bit, ui high_bit, uc exp, uc sign);
void shift_bdecimal_to_high(bdecimal *bdec);
ui singl_high_shift(ui num);
ui singl_low_shift(ui num);
int is_empty_dec(s21_decimal dec);
uc shift_bdecimal_to_low(bdecimal *bdec);
char *print_dec(s21_decimal dec);
bdecimal exclusive_or(bdecimal value_1, bdecimal value_2);
bdecimal bit_and(bdecimal value_1, bdecimal value_2);
bdecimal negative(bdecimal value_1);
bdecimal simple_add(bdecimal value_1, bdecimal value_2);
void full_add(bdecimal value_1, bdecimal value_2, bdecimal *result_bdec);
void full_sub(bdecimal value_1, bdecimal value_2, bdecimal *result_bdec);
bdecimal simple_mul(bdecimal value_1, bdecimal value_2);
bdecimal simple_div(bdecimal value_1, bdecimal value_2);
bdecimal full_div(bdecimal value_1, bdecimal value_2);
uc sign_def(bdecimal value_1, bdecimal value_2);
uc sum_to_divided(bdecimal *temp_big_1, bdecimal *temp_divider);
uc mul_to_exp(bdecimal temp_big_1, bdecimal *temp_divider);
void normalize_bdecimal(bdecimal *value_1, bdecimal *value_2);
void cast_by_exp(bdecimal *bdec, uc exp);
int bdecimal_to_decimal(bdecimal *bdec, s21_decimal *dec_rez);
uc round_bdecimal(bdecimal *bdec_rounded, int fract_part, int int_part);
uc get_big_fract_part(bdecimal bdec);
void fill_dec_from_big(bdecimal bdec, s21_decimal *dec);
uc is_big_converted_to_dec(bdecimal bdec);
uc check_high_ints_big(bdecimal bdec);
s21_decimal simple_floor(s21_decimal dec);
s21_decimal reduce_exp_dec(s21_decimal dec, uc reduce_num);
int bdecimal_is_less(bdecimal value_1, bdecimal value_2);
int bdecimal_is_equal(bdecimal value_1, bdecimal value_2);
int bdecimal_is_greater(bdecimal value_1, bdecimal value_2);
int bdecimal_is_greater_or_equal(bdecimal value_1, bdecimal value_2);
int bdecimal_is_not_equal(bdecimal value_1, bdecimal value_2);
int bdecimal_is_less_or_equal(bdecimal value_1, bdecimal value_2);
int bdecimal_is_to_equals(bdecimal value_1, bdecimal value_2);
bdecimal simple_mod(bdecimal value_1, bdecimal value_2);
bdecimal simple_sub(bdecimal value_1, bdecimal value_2);
uc is_empty_bdecimal(bdecimal bdec);

#endif  // SRC_S21_DECIMAL_H_
