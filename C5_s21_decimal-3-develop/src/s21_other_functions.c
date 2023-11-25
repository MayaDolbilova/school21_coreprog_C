#include "limits.h"
#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  int sign = s21_get_sign(value);
  *result = value;
  if (sign == 1) {
    s21_set_bit(result, 127, 0);
  } else {
    s21_set_bit(result, 127, 1);
  }
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  long double difference = 0.0;
  if (s21_get_scale(value)) {
    long double fl_to_int = 0.0;
    s21_from_decimal_to_double(value, &fl_to_int);
    fl_to_int = trunc(fl_to_int);
    if (fl_to_int < 0.0) {
      s21_set_bit(result, 127, 1);
      fl_to_int *= -1;
    }
    for (int i = 0; fl_to_int >= 1 && i < 96; i++) {
      fl_to_int = floor(fl_to_int) / 2;
      difference = fl_to_int - floor(fl_to_int);
      if (difference > 0.0) {
        s21_set_bit(result, i, 1);
      } else {
        s21_set_bit(result, i, 0);
      }
    }
    s21_set_scale(result, 0);
  } else {
    s21_copy_decimal(result, value);
  }
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  int error = 0;
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  s21_decimal one = {{1, 0, 0, 0}};
  if (scale != 0) {
    error = s21_truncate(value, result);
    if (error == 0 && sign == 1 && !s21_is_equal(*result, value)) {
      error = s21_sub(*result, one, result);
    }
  } else {
    s21_copy_decimal(result, value);
  }
  if (error != 0) {
    error = 1;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  int error = 0;
  int scale = s21_get_scale(value);
  long double new_float = 0.0;
  long double difference = 0.0;
  if (scale != 0) {
    error = s21_from_decimal_to_double(value, &new_float);
    new_float = round(new_float);
    if (new_float < 0.0) {
      s21_set_bit(result, 127, 1);
      new_float *= -1;
    }
    for (int i = 0; new_float >= 1 && i < 96; i++) {
      new_float = floor(new_float) / 2;
      difference = new_float - floor(new_float);
      if (difference > 0.0) {
        s21_set_bit(result, i, 1);
      } else {
        s21_set_bit(result, i, 0);
      }
    }
    s21_set_scale(result, 0);
  } else {
    s21_copy_decimal(result, value);
  }
  if (error != 0) {
    error = 1;
  }
  return error;
}
