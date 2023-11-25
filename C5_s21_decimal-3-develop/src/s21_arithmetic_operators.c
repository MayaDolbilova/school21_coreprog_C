#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_zero_decimal(result);
  int result_sign = 0;
  int error = 0;
  int biggest_scale = 0;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  if (sign_1 == 1 && sign_2 == 1) {
    result_sign = 1;
  }
  if (sign_1 != sign_2) {  // сложение чисел с разным знаком
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
    if (sign_1 == 1) {
      s21_sub(value_2, value_1, result);
    } else {
      s21_sub(value_1, value_2, result);
    }
  } else {
    s21_big_decimal a = {0};
    s21_big_decimal b = {0};
    s21_big_decimal res = {0};
    int scale_1 = s21_get_scale(value_1);
    int scale_2 = s21_get_scale(value_2);
    int differemce = scale_1 - scale_2;
    if (differemce > 0) {
      biggest_scale = scale_1;
    } else {
      biggest_scale = scale_2;
    }
    s21_convert_to_big_decimal(value_1, &a);
    s21_convert_to_big_decimal(value_2, &b);
    s21_normalization(&a, &b, differemce);
    s21_add_big_dec(a, b, &res);
    int scale = 0;
    scale = s21_post_normalization(&res, biggest_scale);
    if (scale >= 0) {
      s21_convert_to_small_decimal(result, res);
      s21_set_scale(result, scale);
    } else {
      error = 1;
    }
    if (result_sign == 1) {
      s21_set_sign(result);
    }
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);

  return error;
}

void s21_add_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int temp = 0;
  for (int i = 0; i < 256; i++) {
    int number1 = 0;
    number1 = s21_get_bit_big(value_1, i);
    int number2 = 0;
    number2 = s21_get_bit_big(value_2, i);
    if (number1 == 1 && number2 == 1) {
      if (temp == 0) {
        temp = 1;
        // res = 0;
        s21_set_bit_big(result, i, 0);
      } else {
        temp = 1;
        s21_set_bit_big(result, i, 1);
      }
    } else if ((number1 == 1 && number2 == 0) ||
               (number1 == 0 && number2 == 1)) {
      if (temp == 0) {
        temp = 0;
        s21_set_bit_big(result, i, 1);
      } else {
        temp = 1;
        s21_set_bit_big(result, i, 0);
      }
    } else {
      if (temp == 0) {
        temp = 0;
        s21_set_bit_big(result, i, 0);
      } else {
        temp = 0;
        s21_set_bit_big(result, i, 1);
      }
    }
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal a = {0}, b = {0}, res = {0};
  int error = 0;
  int scale_1 = s21_get_scale(value_1);
  int scale_2 = s21_get_scale(value_2);
  int res_scale = scale_1 + scale_2;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int res_sign = 0;
  if (sign_1 != sign_2) {
    res_sign = 1;
  }
  s21_convert_to_big_decimal(value_1, &a);
  s21_convert_to_big_decimal(value_2, &b);
  error = s21_big_mul(a, b, &res);
  s21_convert_to_small_decimal(result, res);
  s21_set_scale(result, res_scale);
  if (res_sign == 1) {
    s21_set_sign(result);
  }
  return error;
}

int s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result) {
  int error = 0;
  s21_big_decimal temp = {0};
  if (s21_bit_mul(value_1, value_2, &temp)) {
    error = 1;
  } else {
    *result = temp;
  }
  return error;
}

int s21_bit_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result) {
  s21_big_decimal temp = {0};
  int error = 0;
  for (int i = 0; i < 256; i++) {
    if (s21_get_bit_big(value_2, i)) {
      s21_add_big_dec(temp, value_1, &temp);
      s21_shift_left(&value_1);
    } else {
      s21_shift_left(&value_1);
    }
  }
  temp.bits[8] = result->bits[8];
  *result = temp;
  return error;
}

void s21_shift_left(s21_big_decimal *value) {
  int bit[7];
  for (int i = 31, j = 0; j < 7; i += 32, j++)
    bit[j] = s21_get_bit_big(*value, i);
  for (int i = 0; i < 8; i++) value->bits[i] <<= 1;
  for (int i = 32, j = 0; j < 7; i += 32, j++)
    if (bit[j]) s21_set_bit_big(value, i, 1);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_zero_decimal(result);
  int result_sign = 0;
  int error = 0;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  if (sign_1 == 0 && sign_2 == 1) {
    s21_set_bit(&value_2, 127, 0);
    error = s21_add(value_1, value_2, result);
  } else if (sign_1 == 1 && sign_2 == 0) {
    if (sign_1 == 1) {
      result_sign = 1;
    }
    s21_set_bit(&value_1, 127, 0);
    error = s21_add(value_1, value_2, result);
  } else if (sign_1 == 1 && sign_2 == 1) {
    s21_decimal temp = value_1;
    value_1 = value_2;
    value_2 = temp;
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
    error = s21_big_sub(value_1, value_2, result);
  } else {
    error = s21_big_sub(value_1, value_2, result);
  }
  if (result_sign == 1) {
    s21_set_sign(result);
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

int s21_big_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int scale = 0;
  s21_big_decimal a = {0};
  s21_big_decimal b = {0};
  s21_big_decimal res = {0};
  int bigger_scale = 0;
  s21_convert_to_big_decimal(value_1, &a);
  s21_convert_to_big_decimal(value_2, &b);

  int scale_1 = s21_get_scale(value_1);
  int scale_2 = s21_get_scale(value_2);
  int difference = scale_1 - scale_2;

  if (difference > 0) {
    s21_set_scale(&value_2, scale_1);
    bigger_scale = scale_1;
  } else {
    s21_set_scale(&value_1, scale_2);
    bigger_scale = scale_2;
  }
  if (difference != 0) {
    s21_normalization(&a, &b, difference);
  }
  if (s21_is_greater_big_decimal(b, a)) {
    s21_big_decimal temporary = a;
    a = b;
    b = temporary;
    s21_set_sign(result);
  }
  s21_sub_big_dec(a, b, &res);
  scale = s21_post_normalization(&res, bigger_scale);
  if (scale >= 0) {
    s21_convert_to_small_decimal(result, res);
    s21_set_scale(result, scale);
  } else {
    error = 1;
  }
  return error;
}

int s21_sub_big_dec(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  for (int i = 0; i < 256; i++) {
    int number1 = s21_get_bit_big(value_1, i);
    int number2 = s21_get_bit_big(value_2, i);
    if (number1 == 0 && number2 == 1) {
      int index_one = 0;
      s21_set_bit_big(result, i, 1);
      s21_find_one(value_1, i, &index_one);
      s21_change_to_zero(&value_1, index_one, i);
    } else {
      if (number1 == 1 && number2 == 0) {
        s21_set_bit_big(result, i, 1);
      } else {
        s21_set_bit_big(result, i, 0);
      }
    }
  }
  return 0;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_zero_decimal(result);
  int error = 0;
  s21_decimal res = {{0, 0, 0, 0}};
  error = s21_div(value_1, value_2, &res);
  if (error == 0) {
    error = s21_mul(value_2, res, &res);
    error = s21_sub(value_1, res, result);
  }
  *result = res;
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_zero_decimal(result);
  int res_func = 0, exp = 0, stp = 0;
  s21_big_decimal value_1_big = {0}, value_2_big = {0};

  if (s21_search_bits(value_2) > 95) {
    res_func = 3;
  } else {
    int bits_c_1 = s21_search_scale(value_1);
    int bits_c_2 = s21_search_scale(value_2);

    int diff = bits_c_1 - bits_c_2;
    int code = s21_search_sign(&value_1, &value_2);

    s21_convert_to_big_decimal(value_1, &value_1_big);
    s21_convert_to_big_decimal(value_2, &value_2_big);
    s21_normalization(&value_1_big, &value_2_big, diff);
    s21_convert_to_small_decimal(&value_1, value_1_big);
    s21_convert_to_small_decimal(&value_2, value_2_big);

    if (diff < 0) {
      diff = -diff;
      value_1.bits[3] = ((value_1.bits[3] >> 16) + diff) << 16;
    } else if (diff > 0) {
      value_2.bits[3] = ((value_2.bits[3] >> 16) + diff) << 16;
    }

    while (s21_is_greater_or_equal(value_1, value_2) ||
           s21_is_equal(value_1, value_2)) {
      exp = search_deg(&value_1, value_2);
      shift_bits_left_res(result, &exp);
    }

    if (s21_search_bits(value_1) <= 95) {
      s21_decimal null_d = {{0, 0, 0, 0}};
      s21_decimal mul_dec = {{10, 0, 0, 0}};
      for (int i = 0; i < 8 && s21_is_not_equal(value_1, null_d); i++) {
        while (s21_is_less(value_1, value_2)) {
          s21_mul(value_1, mul_dec, &value_1);
          stp++;
        }
        if (s21_search_bits(value_1) < 96) s21_mul(*result, mul_dec, result);
        while (s21_is_greater(value_1, value_2) ||
               s21_is_equal(value_1, value_2)) {
          exp = search_deg(&value_1, value_2);
          shift_bits_left_res(result, &exp);
        }
      }
    }
    result->bits[3] = ((result->bits[3] >> 16) | stp) << 16;
    if (code) result->bits[3] = result->bits[3] | 2147483648;
  }
  return res_func;
}

int s21_search_sign(s21_decimal *value_1, s21_decimal *value_2) {
  int code = 0;

  if ((value_1->bits[3] >> 31) && (value_2->bits[3] >> 31)) {
    value_1->bits[3] = s21_set_bit(value_1, 127, 0);
    value_2->bits[3] = s21_set_bit(value_2, 127, 0);
    code = 0;
  } else if ((value_1->bits[3] >> 31) && !(value_2->bits[3] >> 31)) {
    value_1->bits[3] = s21_set_bit(value_1, 127, 0);
    code = 1;
  } else if (!(value_1->bits[3] >> 31) && (value_2->bits[3] >> 31)) {
    value_2->bits[3] = s21_set_bit(value_2, 127, 0);
    code = 1;
  }
  return code;
}

void shift_bits_left_res(s21_decimal *result, int *exp) {
  s21_decimal exp_res = {0};
  exp_res.bits[0] = exp_res.bits[0] | 1;
  shift_bits_left(&exp_res, exp);
  s21_add(exp_res, *result, result);
}

int search_deg(s21_decimal *value_1, s21_decimal value_2) {
  /* Ищем ближайшую степень к делимому */
  int bits_c_1 = s21_search_bits(*value_1);
  int bits_c_2 = s21_search_bits(value_2);
  int bits_count = bits_c_1 - bits_c_2;
  if (bits_count < 0) bits_count = -bits_count;
  shift_bits_left(&value_2, &bits_count);
  while (s21_is_less(*value_1, value_2)) {
    shift_bits_right(&value_2);
    bits_count--;
  }
  s21_sub(*value_1, value_2, value_1);
  return bits_count;
}

int s21_search_scale(s21_decimal value) {
  int exp = 0;
  if ((value.bits[3] & MASK_SUB) >> 31 == 1)
    exp = (value.bits[3] ^ (1 << 31)) >> 16;
  else
    exp = value.bits[3] >> 16;
  return exp;
}

int s21_search_bits(s21_decimal value) {
  int bits_c = 0, count = 0;  // до первого вхождения числа.
  for (int i = 2; i >= 0 && !count; i--)
    for (int j = 0; j < 32 && !count; j++) {
      if ((value.bits[i] & (0b10000000000000000000000000000000 >> j))) count++;
      if (!count) bits_c++;
    }
  return bits_c;
}

int exp_research(s21_decimal value) {
  int exp = 0;
  if ((value.bits[3] & MASK_SUB) >> 31 == 1)
    exp = (value.bits[3] ^ (1 << 31)) >> 16;
  else
    exp = value.bits[3] >> 16;
  return exp;
}

void shift_bits_right(s21_decimal *value) {
  value->bits[0] = value->bits[0] >> 1;
  if ((value->bits[1] & 1) == 1)
    value->bits[0] = value->bits[0] | 0b10000000000000000000000000000000;

  value->bits[1] = value->bits[1] >> 1;
  if ((value->bits[2] & 1) == 1)
    value->bits[1] = value->bits[1] | 0b10000000000000000000000000000000;

  value->bits[2] = value->bits[2] >> 1;
}

void shift_bits_left(s21_decimal *value, int *bits_count) {
  int count = 0;
  while (*bits_count >= count) {
    value->bits[2] = value->bits[2] << 1;
    if ((value->bits[1] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[2] = value->bits[2] | 1;
    value->bits[1] = value->bits[1] << 1;
    if ((value->bits[0] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[1] = value->bits[1] | 1;
    value->bits[0] = value->bits[0] << 1;
    count++;
  }
}
