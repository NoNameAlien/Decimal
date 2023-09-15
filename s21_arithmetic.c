#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bdecimal bdecimal_1 = decimal_to_bdecimal(value_1);
  bdecimal bdecimal_2 = decimal_to_bdecimal(value_2);
  bdecimal result_bdec = decimal_to_bdecimal(*result);

  normalize_bdecimal(&bdecimal_1, &bdecimal_2);

  full_add(bdecimal_1, bdecimal_2, &result_bdec);

  int overflow = bdecimal_to_decimal(&result_bdec, result);
  int status = OK;
  if (overflow) {
    if (get_sign(value_1.bits[3])) {
      status = NEGINF;
    } else {
      status = INF;
    }
  } else if (is_empty_dec(*result)) {
    status = NEGINF;
  }

  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bdecimal bdecimal_1 = decimal_to_bdecimal(value_1);
  bdecimal bdecimal_2 = decimal_to_bdecimal(value_2);
  bdecimal result_bdec = decimal_to_bdecimal(*result);

  normalize_bdecimal(&bdecimal_1, &bdecimal_2);

  full_sub(bdecimal_1, bdecimal_2, &result_bdec);

  int overflow = bdecimal_to_decimal(&result_bdec, result);
  int status = OK;
  if (overflow) {
    if (get_sign(value_2.bits[3])) {
      status = NEGINF;
    } else {
      status = INF;
    }
  } else if (is_empty_dec(*result)) {
    status = NEGINF;
  }
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bdecimal bdecimal_1 = decimal_to_bdecimal(value_1);
  bdecimal bdecimal_2 = decimal_to_bdecimal(value_2);
  bdecimal result_bdec = decimal_to_bdecimal(*result);

  result_bdec = simple_mul(bdecimal_1, bdecimal_2);
  set_exp(&result_bdec.mantice,
          get_exp(bdecimal_2.mantice) + get_exp(bdecimal_1.mantice));

  int overflow = bdecimal_to_decimal(&result_bdec, result);
  int status = OK;
  if (overflow) {
    if (get_sign(value_1.bits[3]) ^ get_sign(value_2.bits[3])) {
      status = NEGINF;
    } else {
      status = INF;
    }
  } else if (is_empty_dec(*result)) {
    status = NEGINF;
  }
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  bdecimal bdecimal_1 = decimal_to_bdecimal(value_1);
  bdecimal bdecimal_2 = decimal_to_bdecimal(value_2);
  bdecimal result_bdec = decimal_to_bdecimal(*result);

  normalize_bdecimal(&bdecimal_1, &bdecimal_2);
  int status = OK;
  // Деление на ноль
  if (is_empty_bdecimal(bdecimal_2)) {
    status = DIV_0;

  } else {
    result_bdec = full_div(bdecimal_1, bdecimal_2);
  }

  int overflow = bdecimal_to_decimal(&result_bdec, result);

  if (overflow && status != 3) {
    if (get_sign(value_1.bits[3]) ^ get_sign(value_2.bits[3])) {
      status = NEGINF;
    } else {
      status = INF;
    }
  } else if (is_empty_dec(*result) && status != 3) {
    status = NEGINF;
  }
  return status;
}
