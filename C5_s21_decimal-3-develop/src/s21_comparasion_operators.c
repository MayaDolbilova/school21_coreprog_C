#include "s21_decimal.h"

int s21_compare(s21_decimal a, s21_decimal b) {
  int flag = 3;
  s21_decimal c = {0};
  c = a;
  s21_decimal d = {0};
  d = b;
  int sign_1 = s21_get_sign(a);
  int sign_2 = s21_get_sign(b);

  if (sign_1 == 1 && sign_2 == 0) {
    flag = 1;  // первое число меньше потому что отрицательное
  } else if (sign_2 == 1 && sign_1 == 0) {
    flag = 2;  // второе число меньше потому что отрицательное
  } else {     // знаки равны
    if (a.bits[3] != b.bits[3]) {
      s21_big_decimal c1 = {0};
      s21_big_decimal d1 = {0};
      int dif = s21_get_scale(a) - s21_get_scale(b);
      s21_convert_to_big_decimal(a, &c1);
      s21_convert_to_big_decimal(b, &d1);
      if (dif > 0) {
        s21_normalization(&c1, &d1, dif);
      } else if (dif < 0) {
        s21_normalization(&c1, &d1, dif);
      }
      s21_convert_to_small_decimal(&c, c1);
      s21_convert_to_small_decimal(&d, d1);
      // s21_small_norm(&c, &d, dif);
    }
    if (sign_1 == 0 && sign_2 == 0) {  // оба положительные
      for (int i = 2; i >= 0; i--) {
        if (c.bits[i] != d.bits[i]) {
          if (c.bits[i] > d.bits[i]) {
            flag = 2;
            break;
          } else {
            flag = 1;
            break;
          }
        }
      }
    } else {  // оба отрицательные
      for (int i = 2; i >= 0; i--) {
        if (c.bits[i] != d.bits[i]) {
          if (c.bits[i] > d.bits[i]) {
            flag = 1;  // тут был 1
            break;
          } else {
            flag = 2;  // тут была 2
            break;
          }
        }
      }
    }
  }
  if (!a.bits[0] && !a.bits[1] && !a.bits[2] && !b.bits[0] && !b.bits[1] &&
      !b.bits[2]) {
    flag = 3;
  }
  return flag;
}

int s21_is_less(s21_decimal a, s21_decimal b) {  // возвращает 1 если a меньше b
  int res = s21_compare(a, b);
  int flag = 0;
  if (res == 1) {
    flag = 1;
  }
  return flag;
}

int s21_is_greater(s21_decimal a,
                   s21_decimal b) {  // возвращает 1 если a больше b
  int flag = 1;
  int res = s21_compare(a, b);
  if (res == 3 || res == 1) {
    flag = 0;
  }
  return flag;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int res = s21_compare(a, b);
  int flag = 0;
  if (res == 1 || res == 3) {
    flag = 1;
  }
  return flag;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  res = s21_compare(a, b);  // если 2 или 3
  int flag = 0;
  if (res == 2 || res == 3) {
    flag = 1;
  }
  return flag;
}
int s21_is_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  res = s21_compare(a, b);
  int flag = 0;
  if (res == 3) {
    flag = 1;
  }
  return flag;
}
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int res = s21_compare(a, b);
  int flag = 0;
  if (res != 3) {
    flag = 1;
  }
  return flag;
}
