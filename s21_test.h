#ifndef S21_TEST_H
#define S21_TEST_H

#include "s21_decimal.h"

typedef struct Origin_dec {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal add;
  s21_decimal sub;
  s21_decimal mul;
  s21_decimal div1;
  s21_decimal div2;
  int compare12;
  int compare21;
  int int_itod;
  s21_decimal dec_itod;
  float float_ftod;
  s21_decimal dec_ftod;
  s21_decimal floor1;
  s21_decimal floor2;
  s21_decimal round1;
  s21_decimal round2;
  s21_decimal trunc1;
  s21_decimal trunc2;
  s21_decimal negate1;
  s21_decimal negate2;
  int count_lines;

} Origin_dec;

void set_float_from_file(float *, char *);
void set_int_from_file(int *, char *);
void set_dec_from_file(s21_decimal *, char *);
void set_origin_decs(Origin_dec *, unsigned char);
char *find_str_by_match(char *);
int check_lines_count();

#endif
