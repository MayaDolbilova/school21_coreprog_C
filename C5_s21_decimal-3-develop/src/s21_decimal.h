#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK_SUB 0b10000000000111000000000000000000

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

// арифметика
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Сравнение
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);

// Доп. функции
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Битовые операции
int s21_get_bit(s21_decimal value, int bitindex);
int s21_set_bit(s21_decimal *decl, int bitindex, int number);
int s21_int_number(int index);
int s21_bit_number(int index);
int s21_get_sign(s21_decimal value);
void s21_zero_decimal(s21_decimal *dst);
void s21_set_sign(s21_decimal *dst);
int s21_get_scale(s21_decimal dst);
int s21_get_exp(s21_decimal value);
void s21_set_scale(s21_decimal *dst, int scale);

void s21_copy_decimal(s21_decimal *d1, s21_decimal d2);
int s21_is_decimal_not_empty(s21_decimal dst);

// big decimal functions
void s21_convert_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2);
void s21_convert_to_small_decimal(s21_decimal *value_1,
                                  s21_big_decimal value_2);
void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2,
                       int diff);
int s21_post_normalization(s21_big_decimal *result, int scale);
void s21_add_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void s21_shift_left(s21_big_decimal *value);
int s21_bit_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result);
int s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result);
int s21_get_bit_big(s21_big_decimal dst, int index);
void s21_set_bit_big(s21_big_decimal *dst, int index, int bit);
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2);
void s21_shift_left(s21_big_decimal *value);
int s21_big_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void s21_decreace_scale_big_decimal(s21_big_decimal *dst, int n);
void s21_increase_scale_big_decimal(s21_big_decimal *dst, int n);
void s21_zero_big_decimal(s21_big_decimal *dst);
void s21_add_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int s21_find_one(s21_big_decimal value, int index_now, int *index_one);
int s21_change_to_zero(s21_big_decimal *value, int index_one, int index_now);
int s21_compare(s21_decimal a, s21_decimal b);
int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);
void s21_find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                      int *bit_1, int *bit_2);
int s21_shift_big_dec_left(s21_big_decimal *dst, int num);
int s21_equation_bits_big_decimal(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2);
void s21_shift_big_dec_right(s21_big_decimal *dst, int num);
int s21_is_big_decimal_not_empty(s21_big_decimal dst);

int s21_search_sign(s21_decimal *value_1, s21_decimal *value_2);
int search_deg(s21_decimal *value_1, s21_decimal value_2);
int s21_search_scale(s21_decimal value);
int exp_research(s21_decimal value);
void shift_bits_right(s21_decimal *value);
int s21_search_bits(s21_decimal value);
void shift_bits_left_res(s21_decimal *result, int *exp);
void shift_bits_left(s21_decimal *value, int *bits_count);

int s21_search_scale_big_decimal(s21_big_decimal value);
int s21_search_sign_big_decimal(s21_big_decimal *value_1,
                                s21_big_decimal *value_2);
int search_deg_big_decimal(s21_big_decimal *value_1, s21_big_decimal value_2);
void shift_bits_left_res_big_decimal(s21_big_decimal *result, int *exp);
int s21_search_bits_big_decimal(s21_big_decimal value);
void shift_bits_left_big_decimal(s21_big_decimal *value, int *bits_count);
void shift_bits_right_big_decimal(s21_big_decimal *value);

#endif  // SRC_S21_DECIMAL_H_