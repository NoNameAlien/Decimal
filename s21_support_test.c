#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "s21_test.h"

void set_origin_decs(Origin_dec* dec, unsigned char index) {
  char format[24] = "";
  snprintf(format, sizeof(format), "dec_%u.1", index);
  set_dec_from_file(&dec->dec1, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "dec_%u.2", index);
  set_dec_from_file(&dec->dec2, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "add_%u", index);
  set_dec_from_file(&dec->add, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "sub_%u", index);
  set_dec_from_file(&dec->sub, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "mul_%u", index);
  set_dec_from_file(&dec->mul, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "div_%u_dec_%u.1", index, index);
  set_dec_from_file(&dec->div1, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "div_%u_dec_%u.2", index, index);
  set_dec_from_file(&dec->div2, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "intToDec_%u", index);
  set_int_from_file(&dec->int_itod, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "compare_1_%u", index);
  set_int_from_file(&dec->compare12, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "compare_2_%u", index);
  set_int_from_file(&dec->compare21, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "floatToDec_%u", index);
  set_float_from_file(&dec->float_ftod, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "decToInt_%u", index);
  set_dec_from_file(&dec->dec_itod, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "decToFloat_%u", index);
  set_dec_from_file(&dec->dec_ftod, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "floor_%u_dec_%u.1", index, index);
  set_dec_from_file(&dec->floor1, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "floor_%u_dec_%u.2", index, index);
  set_dec_from_file(&dec->floor2, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "round_%u_dec_%u.1", index, index);
  set_dec_from_file(&dec->round1, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "round_%u_dec_%u.2", index, index);
  set_dec_from_file(&dec->round2, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "trunc_%u_dec_%u.1", index, index);
  set_dec_from_file(&dec->trunc1, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "trunc_%u_dec_%u.2", index, index);
  set_dec_from_file(&dec->trunc2, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "negate_%u_dec_%u.1", index, index);
  set_dec_from_file(&dec->negate1, format);
  memset(format, '\0', sizeof(format));

  snprintf(format, sizeof(format), "negate_%u_dec_%u.2", index, index);
  set_dec_from_file(&dec->negate2, format);
  memset(format, '\0', sizeof(format));
}

void set_float_from_file(float* float_dec, char* find_str) {
  char* dec_str = calloc(strlen(find_str_by_match(find_str)) + 1, sizeof(char));
  dec_str = find_str_by_match(find_str);
  for (unsigned short i = 0; i < strlen(find_str_by_match(find_str)); i++) {
    if (dec_str[i] == ',') dec_str[i] = '.';
  }
  sscanf(dec_str, "%*s %e", float_dec);
}

void set_int_from_file(int* int_dec, char* find_str) {
  char* dec_str = find_str_by_match(find_str);
  sscanf(dec_str, "%*s %d", int_dec);
}

void set_dec_from_file(s21_decimal* dec, char* find_str) {
  char* dec_str = find_str_by_match(find_str);
  char sign = 0;
  unsigned char exp = 0;
  sscanf(dec_str, "%*s %hhd %hhu %u %u %u", &sign, &exp, &(dec->bits[2]),
         &(dec->bits[1]), &(dec->bits[0]));
  set_exp(&dec->bits[3], exp);
  set_sign(&dec->bits[3], sign);

  free(dec_str);
}

char* find_str_by_match(char* search_str) {
  regex_t reg_ptr;
  FILE* file = NULL;
  size_t buf_size = 256;
  char* buf_str;
  buf_str = (char*)malloc(buf_size * sizeof(char));
  if ((file = fopen("test.tst", "r")) != NULL) {
    if (!regcomp(&reg_ptr, search_str, REG_ICASE)) {
      while (getline(&buf_str, &buf_size, file) != -1) {
        if (!regexec(&reg_ptr, buf_str, 0, NULL, 0)) {
          break;
        }
      }
      regfree(&reg_ptr);
    }
    fclose(file);
  }
  return buf_str;
}

int check_lines_count() {
  regex_t reg_ptr;
  FILE* file = NULL;
  size_t buf_size = 256;
  char* buf_str;
  int count_lines = 0;
  buf_str = (char*)malloc(buf_size * sizeof(char));
  if ((file = fopen("test.tst", "r")) != NULL) {
    if (!regcomp(&reg_ptr, "add_", REG_ICASE)) {
      while (getline(&buf_str, &buf_size, file) != -1) {
        if (!regexec(&reg_ptr, buf_str, 0, NULL, 0)) {
          count_lines++;
        }
      }
      regfree(&reg_ptr);
    }
    fclose(file);
  }
  return count_lines;
}
