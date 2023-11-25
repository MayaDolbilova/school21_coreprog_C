#include "s21_decimal.h"

void s21_zero_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int s21_int_number(int index) { return index / 32; }

int s21_bit_number(int index) { return index % 32; }

int s21_get_bit(s21_decimal dec, int bitindex) {
  int mask = 1 << s21_bit_number(bitindex);
  return !!(dec.bits[s21_int_number(bitindex)] & mask);
}

int s21_set_bit(s21_decimal *decl, int bitindex, int number) {
  int mask = 1u << s21_bit_number(bitindex);
  int result = 0;
  if (s21_int_number(bitindex) < 4 && number) {
    result = !!(decl->bits[s21_int_number(bitindex)] |= mask);
  } else if (s21_int_number(bitindex) < 4 && number == 0) {
    result = !!(decl->bits[s21_int_number(bitindex)] &= ~mask);
  }
  return result;
}

int s21_get_sign(s21_decimal value) { return s21_get_bit(value, 127); }

void s21_set_sign(s21_decimal *dst) { dst->bits[3] = dst->bits[3] | 1u << 31; }

int s21_get_scale(s21_decimal dst) {
  int mask = 127 << 16;
  int scale = (mask & dst.bits[3]) >> 16;
  return scale;
}

int s21_get_exp(s21_decimal value) {
  return (value.bits[3] & 0x00FF0000) >> 16;
}

void s21_set_scale(s21_decimal *dst,
                   int scale) {  // устанавливаем скейл (int scale) в децимал на
                                 // который указатель
  int sign = 0;
  sign = s21_get_sign(*dst);  // узнаем знак децимала
  dst->bits[3] = 0;           // обнуляем скейл децимала
  scale <<= 16;  // то же самое что умножить scale на 2 ы 16 степени перемещаем
                 // его на 16 бит как просят в задании
  dst->bits[3] =
      scale |
      dst->bits[3];  // зачем-то применяетс операция или с нулем я думаю что это
                     // равноценно тому чтобы просто приравнять к скейлу
  if (sign)
    s21_set_sign(
        dst);  // если число отрицательное устанавливаем что оно отрицательное
               // (потому что при обнулении скейла это могло потеряться)
}

void s21_copy_decimal(s21_decimal *d1, s21_decimal d2) {
  for (int i = 127; i >= 0; i--) {
    s21_set_bit(d1, i,
                s21_get_bit(d2, i));  // перемещаем биты из одного в другой
  }
}

int s21_find_one(s21_big_decimal value, int index_now, int *index_one) {
  // находим индекс единицы, у которой будем занимать десяток
  int res = 0;
  while (res != 1) {
    if (s21_get_bit_big(value, index_now) == 1) {
      *index_one = index_now;
      res = 1;
    }
    index_now += 1;
  }
  return 0;
}
int s21_change_to_zero(s21_big_decimal *value, int index_one, int index_now) {
  for (int i = index_now + 1; i < index_one; i++) {
    s21_set_bit_big(value, i, 1);
  }
  s21_set_bit_big(value, index_one, 0);
  return 0;
}
