#include "s21_test.h"

#include <check.h>

#include "s21_decimal.h"

static int count_line;

// convert case --
START_TEST(convert_int_to_dec_test) {
  for (int i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);

    char* ori_str = print_dec(origin_dec.dec_itod);

    s21_decimal s21_itod = {0};
    s21_from_int_to_decimal(origin_dec.int_itod, &s21_itod);

    char* s21_str = print_dec(s21_itod);

    ck_assert_str_eq(ori_str, s21_str);

    free(ori_str);
    free(s21_str);
  }
}
END_TEST

START_TEST(convert_dec_to_int_test) {
  for (int i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal s21_dec = origin_dec.dec_itod;
    int s21_int = 0;
    s21_from_decimal_to_int(s21_dec, &s21_int);

    ck_assert_int_eq(origin_dec.int_itod, s21_int);
  }
}
END_TEST

START_TEST(convert_float_to_dec_test) {
  for (int i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);

    char* ori_str = print_dec(origin_dec.dec_ftod);

    s21_decimal s21_ftod = {0};
    s21_from_float_to_decimal(origin_dec.float_ftod, &s21_ftod);

    char* s21_str = print_dec(s21_ftod);
    ck_assert_str_eq(ori_str, s21_str);

    free(ori_str);
    free(s21_str);
  }

  // float fl_1 = 6347073846.0079878f;
  // char* str_fl_1 = "0 0 0 0 6347074\n";
  // s21_decimal s21_ftod_1 = {0};
  // s21_from_float_to_decimal(fl_1, &s21_ftod_1);
  // char* s21_str_1 = print_dec(s21_ftod_1);
  // ck_assert_str_eq(s21_str_1, str_fl_1);
  // free(s21_str_1);

  float fl_2 = 73846.0000079878f;
  char* str_fl_2 = "0 0 0 0 73846\n";
  s21_decimal s21_ftod_2 = {0};
  s21_from_float_to_decimal(fl_2, &s21_ftod_2);
  char* s21_str_2 = print_dec(s21_ftod_2);
  ck_assert_str_eq(s21_str_2, str_fl_2);
  free(s21_str_2);

  float fl_3 = 73846.79878f;
  char* str_fl_3 = "0 1 0 0 738468\n";
  s21_decimal s21_ftod_3 = {0};
  s21_from_float_to_decimal(fl_3, &s21_ftod_3);
  char* s21_str_3 = print_dec(s21_ftod_3);
  ck_assert_str_eq(s21_str_3, str_fl_3);
  free(s21_str_3);

  float fl_4 = .1009887879878f;
  char* str_fl_4 = "0 7 0 0 1009888\n";
  s21_decimal s21_ftod_4 = {0};
  s21_from_float_to_decimal(fl_4, &s21_ftod_4);
  char* s21_str_4 = print_dec(s21_ftod_4);
  ck_assert_str_eq(s21_str_4, str_fl_4);
  free(s21_str_4);

  // float fl_5 = 634707384699999.0079878f;
  // char* str_fl_5 = "0 0 0 147779 1427964416\n";
  // s21_decimal s21_ftod_5 = {0};
  // s21_from_float_to_decimal(fl_5, &s21_ftod_5);
  // char* s21_str_5 = print_dec(s21_ftod_5);
  // ck_assert_str_eq(s21_str_5, str_fl_5);
  // free(s21_str_5);

  // float fl_6 = 49998999634707384699999.0079878f;
  // char* str_fl_6 = "0 0 2710 1937979889 3554410496\n";
  // s21_decimal s21_ftod_6 = {0};
  // s21_from_float_to_decimal(fl_6, &s21_ftod_6);
  // char* s21_str_6 = print_dec(s21_ftod_6);
  // ck_assert_str_eq(s21_str_6, str_fl_6);
  // free(s21_str_6);

  // float fl_7 = 1.24e21f;
  // char* str_fl_7 = "0 0 67 947189298 3428843520\n";
  // s21_decimal s21_ftod_7 = {0};
  // s21_from_float_to_decimal(fl_7, &s21_ftod_7);
  // char* s21_str_7 = print_dec(s21_ftod_7);
  // ck_assert_str_eq(s21_str_7, str_fl_7);
  // free(s21_str_7);

  float fl_8 = 3.74e-21f;
  char* str_fl_8 = "0 23 0 0 374\n";
  s21_decimal s21_ftod_8 = {0};
  s21_from_float_to_decimal(fl_8, &s21_ftod_8);
  char* s21_str_8 = print_dec(s21_ftod_8);
  ck_assert_str_eq(s21_str_8, str_fl_8);
  free(s21_str_8);

  float fl_9 = -.000000000001009887879878f;
  char* str_fl_9 = "1 18 0 0 1009888\n";
  s21_decimal s21_ftod_9 = {0};
  s21_from_float_to_decimal(fl_9, &s21_ftod_9);
  char* s21_str_9 = print_dec(s21_ftod_9);
  ck_assert_str_eq(s21_str_9, str_fl_9);
  free(s21_str_9);
}
END_TEST

START_TEST(convert_dec_to_float_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal s21_dec = origin_dec.dec_ftod;
    float s21_float = 0;
    s21_from_decimal_to_float(s21_dec, &s21_float);
    ck_assert_float_le(s21_float - origin_dec.float_ftod, 1e-7);
  }
}
END_TEST
// -- convert case

// arithmetic case --
START_TEST(add_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;
    s21_decimal dec_add = {0};
    int erc = s21_add(dec1, dec2, &dec_add);
    char* s21_add = print_dec(dec_add);
    char* ori_add = print_dec(origin_dec.add);
    // printf("add\ns21:%s\nori:%s\n", s21_add, ori_add);
    ck_assert_str_eq(s21_add, ori_add);
    ck_assert_int_eq(erc, 0);
    free(s21_add);
    free(ori_add);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(1, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_add(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 1);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_divs, s_divs, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 1);
    s21_decimal dec2 = set_decimal(1, 0, 0, 0, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_add(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_divs, s_divs, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(1, 0, 0, 0, 0);
    s21_decimal dec2 = set_decimal(1, 0, 0, 0, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_add(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_divs, s_divs, er);
    // printf("%d\n", er);
    free(ori_adds);
    free(s_adds);
  }
}
END_TEST

START_TEST(sub_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;
    s21_decimal dec_sub = {0};
    int erc = s21_sub(dec1, dec2, &dec_sub);
    char* s21_sub = print_dec(dec_sub);
    char* ori_sub = print_dec(origin_dec.sub);
    // printf("sub\ns21:%s\nori:%s\n", s21_sub, ori_sub);
    ck_assert_str_eq(s21_sub, ori_sub);
    ck_assert_int_eq(erc, 0);
    free(s21_sub);
    free(ori_sub);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(1, 0, 0, 0, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_sub(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 1);
    s21_decimal dec2 = set_decimal(1, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_sub(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 1);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
}
END_TEST

START_TEST(mul_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;
    s21_decimal dec_mul = {0};
    s21_mul(dec1, dec2, &dec_mul);
    char* s21_mul = print_dec(dec_mul);
    char* ori_mul = print_dec(origin_dec.mul);
    if (!strcmp(ori_mul, "1 0 0 0 0\0")) {
      // printf("mul\ns21:%s\nori:%s\n", s21_mul, ori_mul);
      ck_assert_str_eq(s21_mul, ori_mul);
    }
    free(s21_mul);
    free(ori_mul);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 1);
    s21_decimal dec2 = set_decimal(2, 0, 0, 0, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_mul(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 1);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(2, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_mul(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 1);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 1);
    s21_decimal dec2 = set_decimal(2, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_mul(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 1);
    s21_decimal dec2 = set_decimal(0, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_mul(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
}
END_TEST

START_TEST(div_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;
    s21_decimal dec_div1 = {0};
    s21_div(dec1, dec2, &dec_div1);
    char* s21_div1 = print_dec(dec_div1);
    char* ori_div1 = print_dec(origin_dec.div1);
    // printf("div1\ns21:%s\nori:%s\n", s21_div1, ori_div1);
    ck_assert_str_eq(s21_div1, ori_div1);
    free(s21_div1);
    free(ori_div1);

    s21_decimal dec_div2 = {0};
    s21_div(dec2, dec1, &dec_div2);
    char* s21_div2 = print_dec(dec_div2);
    char* ori_div2 = print_dec(origin_dec.div2);
    // printf("div2\ns21:%s\nori:%s\n", s21_div2, ori_div2);
    ck_assert_str_eq(s21_div2, ori_div2);
    free(s21_div2);
    free(ori_div2);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(0, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 3);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(12, 0, 0, 15, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 1);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(12, 0, 0, 15, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(0, 0, 0, 0, 0);
    s21_decimal dec2 = set_decimal(12, 0, 0, 15, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char* ori_adds = print_dec(ori_add);
    char* s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 2);
    // printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
}
END_TEST

// -- arithmetic case

// compare --
START_TEST(is_less_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    int s21_isLess = s21_is_less(dec1, dec2);
    int ori_isLess = origin_dec.compare12;
    if (ori_isLess == -1) {
      ori_isLess = 1;
    } else if (ori_isLess == 1 || ori_isLess == 0) {
      ori_isLess = 0;
    }
    ck_assert_int_eq(ori_isLess, s21_isLess);
  }
  s21_decimal dec1 = set_rand_decimal();
  s21_decimal dec2 = dec1;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  s21_decimal dec01 = set_decimal(0, 0, 0, 0, 0);
  s21_decimal dec02 = dec01;
  ck_assert_int_eq(s21_is_less(dec01, dec02), 0);
}
END_TEST

START_TEST(is_less_or_equal_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    int s21_isLess = s21_is_less_or_equal(dec1, dec2);
    int ori_isLess = origin_dec.compare12;
    if (ori_isLess == -1 || ori_isLess == 0) {
      ori_isLess = 1;
    } else if (ori_isLess == 1) {
      ori_isLess = 0;
    }
    ck_assert_int_eq(ori_isLess, s21_isLess);
  }
  s21_decimal dec1 = set_rand_decimal();
  s21_decimal dec2 = dec1;
  ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 1);
  s21_decimal dec01 = set_decimal(0, 0, 0, 0, 0);
  s21_decimal dec02 = dec01;
  ck_assert_int_eq(s21_is_less_or_equal(dec01, dec02), 1);
}
END_TEST

START_TEST(is_greater_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    int s21_isLess = s21_is_greater(dec1, dec2);
    int ori_isLess = origin_dec.compare12;
    if (ori_isLess == 1) {
      ori_isLess = 1;
    } else if (ori_isLess == -1 || ori_isLess == 0) {
      ori_isLess = 0;
    }
    ck_assert_int_eq(ori_isLess, s21_isLess);
  }
  s21_decimal dec1 = set_rand_decimal();
  s21_decimal dec2 = dec1;
  ck_assert_int_eq(s21_is_greater(dec1, dec2), 0);
  s21_decimal dec01 = set_decimal(0, 0, 0, 0, 0);
  s21_decimal dec02 = dec01;
  ck_assert_int_eq(s21_is_greater(dec01, dec02), 0);
}
END_TEST

START_TEST(is_greater_or_equal_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    int s21_isLess = s21_is_greater_or_equal(dec1, dec2);
    int ori_isLess = origin_dec.compare12;
    if (ori_isLess == 1 || ori_isLess == 0) {
      ori_isLess = 1;
    } else if (ori_isLess == -1) {
      ori_isLess = 0;
    }
    ck_assert_int_eq(ori_isLess, s21_isLess);
  }
  s21_decimal dec1 = set_rand_decimal();
  s21_decimal dec2 = dec1;
  ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);
  s21_decimal dec01 = set_decimal(0, 0, 0, 0, 0);
  s21_decimal dec02 = dec01;
  ck_assert_int_eq(s21_is_greater_or_equal(dec01, dec02), 1);
}
END_TEST

START_TEST(is_equal_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    int s21_isLess = s21_is_equal(dec1, dec2);
    int ori_isLess = origin_dec.compare12;
    if (ori_isLess == 0) {
      ori_isLess = 1;
    } else if (ori_isLess == 1 || ori_isLess == -1) {
      ori_isLess = 0;
    }
    ck_assert_int_eq(ori_isLess, s21_isLess);
  }
  s21_decimal dec1 = set_rand_decimal();
  s21_decimal dec2 = dec1;
  ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
  s21_decimal dec01 = set_decimal(0, 0, 0, 0, 0);
  s21_decimal dec02 = dec01;
  ck_assert_int_eq(s21_is_equal(dec01, dec02), 1);
}
END_TEST

START_TEST(is_not_equal_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    int s21_isLess = s21_is_not_equal(dec1, dec2);
    int ori_isLess = origin_dec.compare12;
    if (ori_isLess == 1 || ori_isLess == -1) {
      ori_isLess = 1;
    } else if (ori_isLess == 0) {
      ori_isLess = 0;
    }
    ck_assert_int_eq(ori_isLess, s21_isLess);
  }
  s21_decimal dec1 = set_rand_decimal();
  s21_decimal dec2 = dec1;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);
  s21_decimal dec01 = set_decimal(0, 0, 0, 0, 0);
  s21_decimal dec02 = dec01;
  ck_assert_int_eq(s21_is_not_equal(dec01, dec02), 0);
}
END_TEST
// -- compare

// other --
START_TEST(s21_floor_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    s21_decimal dec1_floor = {0};
    s21_floor(dec1, &dec1_floor);

    char* sdec1_floor = print_dec(dec1_floor);
    char* sdec1_ori = print_dec(origin_dec.floor1);
    ck_assert_str_eq(sdec1_floor, sdec1_ori);
    free(sdec1_floor);
    free(sdec1_ori);

    s21_decimal dec2_floor = {0};
    s21_floor(dec2, &dec2_floor);
    char* sdec2_floor = print_dec(dec2_floor);
    char* sdec2_ori = print_dec(origin_dec.floor2);
    ck_assert_str_eq(sdec2_floor, sdec2_ori);
    free(sdec2_floor);
    free(sdec2_ori);
  }
}
END_TEST

START_TEST(s21_round_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    s21_decimal dec1_round = {0};
    s21_round(dec1, &dec1_round);

    char* sdec1_round = print_dec(dec1_round);
    char* sdec1_ori = print_dec(origin_dec.round1);
    ck_assert_str_eq(sdec1_round, sdec1_ori);
    free(sdec1_round);
    free(sdec1_ori);

    s21_decimal dec2_round = {0};
    s21_round(dec2, &dec2_round);
    char* sdec2_round = print_dec(dec2_round);
    char* sdec2_ori = print_dec(origin_dec.round2);
    ck_assert_str_eq(sdec2_round, sdec2_ori);
    free(sdec2_round);
    free(sdec2_ori);
  }
}
END_TEST

START_TEST(s21_trunc_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    s21_decimal dec1_trunc = {0};
    s21_truncate(dec1, &dec1_trunc);

    char* sdec1_trunc = print_dec(dec1_trunc);
    char* sdec1_ori = print_dec(origin_dec.trunc1);
    ck_assert_str_eq(sdec1_trunc, sdec1_ori);
    free(sdec1_trunc);
    free(sdec1_ori);

    s21_decimal dec2_trunc = {0};
    s21_truncate(dec2, &dec2_trunc);
    char* sdec2_trunc = print_dec(dec2_trunc);
    char* sdec2_ori = print_dec(origin_dec.trunc2);
    ck_assert_str_eq(sdec2_trunc, sdec2_ori);
    free(sdec2_trunc);
    free(sdec2_ori);
  }
}
END_TEST

START_TEST(s21_negate_test) {
  for (unsigned char i = 0; i < count_line; i++) {
    Origin_dec origin_dec = {0};
    set_origin_decs(&origin_dec, i);
    s21_decimal dec1 = origin_dec.dec1;
    s21_decimal dec2 = origin_dec.dec2;

    s21_decimal dec1_neg = {0};
    s21_negate(dec1, &dec1_neg);

    char* sdec1_neg = print_dec(dec1_neg);
    char* sdec1_ori = print_dec(origin_dec.negate1);
    ck_assert_str_eq(sdec1_neg, sdec1_ori);
    free(sdec1_neg);
    free(sdec1_ori);

    s21_decimal dec2_neg = {0};
    s21_negate(dec2, &dec2_neg);
    char* sdec2_neg = print_dec(dec2_neg);
    char* sdec2_ori = print_dec(origin_dec.negate2);
    ck_assert_str_eq(sdec2_neg, sdec2_ori);
    free(sdec2_neg);
    free(sdec2_ori);
  }
}
END_TEST
// -- other

Suite* convert_suite(void) {
  Suite* s;
  TCase* tc_convert;
  s = suite_create("convert");
  tc_convert = tcase_create("convert_dec");
  tcase_add_test(tc_convert, convert_int_to_dec_test);
  tcase_add_test(tc_convert, convert_dec_to_int_test);
  tcase_add_test(tc_convert, convert_float_to_dec_test);
  tcase_add_test(tc_convert, convert_dec_to_float_test);
  suite_add_tcase(s, tc_convert);
  return s;
}

Suite* arithmetic_suite(void) {
  Suite* s;
  TCase* tc_arithmetic;
  s = suite_create("arithmetic");
  tc_arithmetic = tcase_create("arithmetic_dec");
  tcase_add_test(tc_arithmetic, add_test);
  tcase_add_test(tc_arithmetic, sub_test);
  tcase_add_test(tc_arithmetic, mul_test);
  tcase_add_test(tc_arithmetic, div_test);
  suite_add_tcase(s, tc_arithmetic);
  return s;
}

Suite* compare_suite(void) {
  Suite* s;
  TCase* tc_compare;
  s = suite_create("compare");
  tc_compare = tcase_create("compare_dec");
  tcase_add_test(tc_compare, is_less_test);
  tcase_add_test(tc_compare, is_less_or_equal_test);
  tcase_add_test(tc_compare, is_greater_test);
  tcase_add_test(tc_compare, is_greater_or_equal_test);
  tcase_add_test(tc_compare, is_equal_test);
  tcase_add_test(tc_compare, is_not_equal_test);
  suite_add_tcase(s, tc_compare);
  return s;
}

Suite* other_suite(void) {
  Suite* s;
  TCase* tc_other;
  s = suite_create("other");
  tc_other = tcase_create("other_dec");
  tcase_add_test(tc_other, s21_floor_test);
  tcase_add_test(tc_other, s21_round_test);
  tcase_add_test(tc_other, s21_trunc_test);
  tcase_add_test(tc_other, s21_negate_test);

  suite_add_tcase(s, tc_other);
  return s;
}

int main(void) {
  count_line = check_lines_count();

  int nf;
  SRunner* sr;

  Suite* s1 = convert_suite();
  sr = srunner_create(s1);

  Suite* s2 = arithmetic_suite();
  Suite* s3 = compare_suite();
  Suite* s4 = other_suite();

  srunner_add_suite(sr, s2);
  srunner_add_suite(sr, s3);
  srunner_add_suite(sr, s4);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
