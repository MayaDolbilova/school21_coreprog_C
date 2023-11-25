#include "s21_decimal_tests.h"

START_TEST(s21_less_0) {
  s21_decimal first = {{4412, 5675, 1254, 0b10000000000000000000000000000000}};
  s21_decimal second = {{4412, 5675, 1254, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 1);
}
END_TEST

START_TEST(s21_less_1) {
  s21_decimal first = {{4412, 5675, 1254, 0b00000000000000000000000000000000}};
  s21_decimal second = {{4412, 5675, 1254, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 0);
}
END_TEST

START_TEST(s21_less_2) {
  s21_decimal first = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 0);
}
END_TEST

START_TEST(s21_less_3) {
  s21_decimal first = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 0);
}
END_TEST

START_TEST(s21_less_4) {
  s21_decimal first = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 0);
}
END_TEST

START_TEST(s21_less_5) {
  s21_decimal first = {{4412, 5675, 1254, 0b00000011000000000000000000000000}};
  s21_decimal second = {{4412, 5675, 1254, 0b00000101000000000000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 0);
}
END_TEST

START_TEST(s21_less_6) {
  s21_decimal first = {{4422, 5515, 9254, 0b10000000000000110000000000000000}};
  s21_decimal second = {{6312, 5616, 1844, 0b10000000000001010000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 1);
}
END_TEST

START_TEST(s21_less_7) {
  s21_decimal first = {{4412, 5775, 1254, 0b00000000000001110000000000000000}};
  s21_decimal second = {{4412, 5675, 1254, 0b00000000000001110000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 0);
}
END_TEST

START_TEST(s21_less_8) {
  s21_decimal first = {{4412, 5775, 1254, 0b00000000000010000000000000000000}};
  s21_decimal second = {{4412, 5775, 1254, 0b00000000000001110000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 1);
}
END_TEST

START_TEST(s21_less_9) {
  s21_decimal first = {
      {2147483646, 2147483647, 2147483647, 0b00000000000001110000000000000000}};
  s21_decimal second = {
      {2147483647, 2147483647, 2147483647, 0b00000000000001110000000000000000}};
  ck_assert_int_eq(s21_is_less(first, second), 1);
}
END_TEST

START_TEST(s21_less_10) {
  s21_decimal first = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(s21_is_equal(first, second), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_0) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal a = {{UINT_MAX - 1, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal a = {{UINT_MAX, 1, 0, 0}};
  s21_decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal a = {{UINT_MAX, UINT_MAX - 1, 0, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal a = {{0, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{0, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_10) {
  s21_decimal a = {{0, 0, UINT_MAX, 0}};
  s21_decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_11) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_12) {
  // 2596
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_13) {
  // 3172
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_14) {
  // 3190
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_15) {
  // 3208
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_16) {
  // 3226
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_17) {
  // 3244
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_18) {
  // 3262
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_19) {
  // 3280
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_20) {
  // 3298
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_21) {
  // 3316
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_22) {
  // 3334
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_23) {
  // 3352
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_24) {
  // 3370
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_25) {
  // 3388
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_26) {
  // 3406
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_27) {
  // 3424
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_28) {
  // 3442
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_less_or_equal_29) {
  // 3478
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_greater_0) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_1) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_2) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_greater_3) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_4) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_5) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_6) {
  int num1 = -3;
  int num2 = 3;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_7) {
  float num1 = -3.232446546;
  float num2 = -3.2;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_8) {
  float num1 = -345.232446546;
  float num2 = -3.2;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_greater_9) {
  float num1 = -3.232323233232323233;
  float num2 = -34545124.232446543232446543;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_greater_10) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec6 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_greater(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater(dec6, dec5), 0);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_greater(dec7, dec8), 0);
  ck_assert_int_eq(s21_is_greater(dec8, dec7), 1);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2
  ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater(dec2, dec1), 0);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //   -1.2
  ck_assert_int_eq(s21_is_greater(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater(dec4, dec3), 1);
}
END_TEST

START_TEST(s21_is_greater_11) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  // Возвращаемое значение : 0 - 0   1 - TRUE
}
END_TEST

START_TEST(s21_is_greater_12) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_13) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX - 1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_14) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(s21_is_greater_15) {
  s21_decimal a = {{UINT_MAX, 0, 0, 0}};
  s21_decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(s21_is_greater_16) {
  s21_decimal a = {{UINT_MAX, 1, 0, 0}};
  s21_decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_17) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX - 1, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_18) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(s21_is_greater_19) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_20) {
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  s21_decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_21) {
  s21_decimal a = {{0, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{0, UINT_MAX, UINT_MAX - 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_22) {
  s21_decimal a = {{0, 0, UINT_MAX, 0}};
  s21_decimal b = {{0, 0, UINT_MAX - 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(s21_is_greater_23) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(s21_is_greater_24) {
  // 3820
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_greater_25) {
  // 3838
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_greater_26) {
  // 3856
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_greater_27) {
  // 3874
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_greater_28) {
  // 3892
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_greater_29) {
  // 3910
  s21_decimal src1 = {0};
  s21_decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_greater_or_equal_0) {
  float num1 = 1.375323;
  float num2 = 1.39;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_greater_or_equal_1) {
  int num1 = 2;
  int num2 = 1;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_2) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_3) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_4) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_greater_or_equal_5) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_6) {
  int num1 = 10;
  int num2 = 3;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_7) {
  float num1 = 10423546.34534534;
  float num2 = 3.34534534;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_8) {
  float num1 = -3.34534534;
  float num2 = 3.34534534;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_greater_or_equal_9) {
  float num1 = 1042634.34534534;
  float num2 = 10424546.34534534;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_greater_or_equal_10) {
  float num1 = 10426.34534534;
  float num2 = 104234.345345;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_greater_or_equal_11) {
  float num1 = 1042.5667777;
  float num2 = 1042.345345;
  s21_decimal dec1 = {0}, dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_greater_or_equal_12) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //
  ck_assert_int_eq(s21_is_greater_or_equal(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec6, dec5), 0);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec7, dec8), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(dec8, dec7), 1);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec2, dec1), 0);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //

  ck_assert_int_eq(s21_is_greater_or_equal(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(dec4, dec3), 1);

  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec9, dec10), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec10, dec9), 1);

  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec12, dec11), 1);
}
END_TEST

START_TEST(s21_is_equal_0) {
  // 5116
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_1) {
  // 5134
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_2) {
  // 5152
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_3) {
  // 5170
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_4) {
  // 5188
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_5) {
  // 5206
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_6) {
  // 5224
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_7) {
  // 5242
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_8) {
  // 5260
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_9) {
  // 5278
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_10) {
  // 5296
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_11) {
  // 5314
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_is_equal_12) {
  // 5332
  s21_decimal src1 = {0}, src2 = {0};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(s21_not_equal_0) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_not_equal_1) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_not_equal_2) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_not_equal_3) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_not_equal_4) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_not_equal_5) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_not_equal_6) {
  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST
START_TEST(s21_not_equal_7) {
  s21_decimal dec3 = {
      {120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
  s21_decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}};  //
  ck_assert_int_eq(s21_is_not_equal(dec3, dec4), 0);
}
END_TEST
START_TEST(s21_not_equal_8) {
  s21_decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};   //  0
  s21_decimal dec6 = {{00, 0, 0, 0b00000000000000010000000000000000}};  //
  ck_assert_int_eq(s21_is_not_equal(dec5, dec6), 0);
}
END_TEST
START_TEST(s21_not_equal_9) {
  s21_decimal dec7 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //   0
  s21_decimal dec8 = {{0, 0, 0, 0b10000000000000000000000000000000}};  //  -0;
  ck_assert_int_eq(s21_is_not_equal(dec7, dec8), 0);
}
END_TEST

Suite *s21_comparison_suite(void) {
  Suite *s;
  TCase *tc1_1;

  s = suite_create("S21 Comparison");
  tc1_1 = tcase_create("Core");
  suite_add_tcase(s, tc1_1);

  // Меньше
  tcase_add_test(tc1_1, s21_less_0);
  tcase_add_test(tc1_1, s21_less_1);
  tcase_add_test(tc1_1, s21_less_2);
  tcase_add_test(tc1_1, s21_less_3);
  tcase_add_test(tc1_1, s21_less_4);
  tcase_add_test(tc1_1, s21_less_5);
  tcase_add_test(tc1_1, s21_less_6);
  tcase_add_test(tc1_1, s21_less_7);
  tcase_add_test(tc1_1, s21_less_8);
  tcase_add_test(tc1_1, s21_less_9);
  tcase_add_test(tc1_1, s21_less_10);

  // Меньше или равно
  tcase_add_test(tc1_1, s21_is_less_or_equal_0);
  tcase_add_test(tc1_1, s21_is_less_or_equal_1);
  tcase_add_test(tc1_1, s21_is_less_or_equal_2);
  tcase_add_test(tc1_1, s21_is_less_or_equal_3);
  tcase_add_test(tc1_1, s21_is_less_or_equal_4);
  tcase_add_test(tc1_1, s21_is_less_or_equal_5);
  tcase_add_test(tc1_1, s21_is_less_or_equal_6);
  tcase_add_test(tc1_1, s21_is_less_or_equal_7);
  tcase_add_test(tc1_1, s21_is_less_or_equal_8);
  tcase_add_test(tc1_1, s21_is_less_or_equal_9);
  tcase_add_test(tc1_1, s21_is_less_or_equal_10);
  tcase_add_test(tc1_1, s21_is_less_or_equal_11);
  tcase_add_test(tc1_1, s21_is_less_or_equal_12);
  tcase_add_test(tc1_1, s21_is_less_or_equal_13);
  tcase_add_test(tc1_1, s21_is_less_or_equal_14);
  tcase_add_test(tc1_1, s21_is_less_or_equal_15);
  tcase_add_test(tc1_1, s21_is_less_or_equal_16);
  tcase_add_test(tc1_1, s21_is_less_or_equal_17);
  tcase_add_test(tc1_1, s21_is_less_or_equal_18);
  tcase_add_test(tc1_1, s21_is_less_or_equal_19);
  tcase_add_test(tc1_1, s21_is_less_or_equal_20);
  tcase_add_test(tc1_1, s21_is_less_or_equal_21);
  tcase_add_test(tc1_1, s21_is_less_or_equal_22);
  tcase_add_test(tc1_1, s21_is_less_or_equal_23);
  tcase_add_test(tc1_1, s21_is_less_or_equal_24);
  tcase_add_test(tc1_1, s21_is_less_or_equal_25);
  tcase_add_test(tc1_1, s21_is_less_or_equal_26);
  tcase_add_test(tc1_1, s21_is_less_or_equal_27);
  tcase_add_test(tc1_1, s21_is_less_or_equal_28);
  tcase_add_test(tc1_1, s21_is_less_or_equal_29);

  // Больше
  tcase_add_test(tc1_1, s21_is_greater_0);
  tcase_add_test(tc1_1, s21_is_greater_1);
  tcase_add_test(tc1_1, s21_is_greater_2);
  tcase_add_test(tc1_1, s21_is_greater_3);
  tcase_add_test(tc1_1, s21_is_greater_4);
  tcase_add_test(tc1_1, s21_is_greater_5);
  tcase_add_test(tc1_1, s21_is_greater_6);
  tcase_add_test(tc1_1, s21_is_greater_7);
  tcase_add_test(tc1_1, s21_is_greater_8);
  tcase_add_test(tc1_1, s21_is_greater_9);
  tcase_add_test(tc1_1, s21_is_greater_10);
  tcase_add_test(tc1_1, s21_is_greater_11);
  tcase_add_test(tc1_1, s21_is_greater_12);
  tcase_add_test(tc1_1, s21_is_greater_13);
  tcase_add_test(tc1_1, s21_is_greater_14);
  tcase_add_test(tc1_1, s21_is_greater_15);
  tcase_add_test(tc1_1, s21_is_greater_16);
  tcase_add_test(tc1_1, s21_is_greater_17);
  tcase_add_test(tc1_1, s21_is_greater_18);
  tcase_add_test(tc1_1, s21_is_greater_19);
  tcase_add_test(tc1_1, s21_is_greater_20);
  tcase_add_test(tc1_1, s21_is_greater_21);
  tcase_add_test(tc1_1, s21_is_greater_22);
  tcase_add_test(tc1_1, s21_is_greater_23);
  tcase_add_test(tc1_1, s21_is_greater_24);
  tcase_add_test(tc1_1, s21_is_greater_25);
  tcase_add_test(tc1_1, s21_is_greater_26);
  tcase_add_test(tc1_1, s21_is_greater_27);
  tcase_add_test(tc1_1, s21_is_greater_28);
  tcase_add_test(tc1_1, s21_is_greater_29);

  // Больше или равно
  tcase_add_test(tc1_1, s21_greater_or_equal_0);
  tcase_add_test(tc1_1, s21_greater_or_equal_1);
  tcase_add_test(tc1_1, s21_greater_or_equal_2);
  tcase_add_test(tc1_1, s21_greater_or_equal_3);
  tcase_add_test(tc1_1, s21_greater_or_equal_4);
  tcase_add_test(tc1_1, s21_greater_or_equal_5);
  tcase_add_test(tc1_1, s21_greater_or_equal_6);
  tcase_add_test(tc1_1, s21_greater_or_equal_7);
  tcase_add_test(tc1_1, s21_greater_or_equal_8);
  tcase_add_test(tc1_1, s21_greater_or_equal_9);
  tcase_add_test(tc1_1, s21_greater_or_equal_10);
  tcase_add_test(tc1_1, s21_greater_or_equal_11);
  tcase_add_test(tc1_1, s21_greater_or_equal_12);
  // Равно
  tcase_add_test(tc1_1, s21_is_equal_0);
  tcase_add_test(tc1_1, s21_is_equal_1);
  tcase_add_test(tc1_1, s21_is_equal_2);
  tcase_add_test(tc1_1, s21_is_equal_3);
  tcase_add_test(tc1_1, s21_is_equal_4);
  tcase_add_test(tc1_1, s21_is_equal_5);
  tcase_add_test(tc1_1, s21_is_equal_6);
  tcase_add_test(tc1_1, s21_is_equal_7);
  tcase_add_test(tc1_1, s21_is_equal_8);
  tcase_add_test(tc1_1, s21_is_equal_9);
  tcase_add_test(tc1_1, s21_is_equal_10);
  tcase_add_test(tc1_1, s21_is_equal_11);
  tcase_add_test(tc1_1, s21_is_equal_12);
  // Не равно
  tcase_add_test(tc1_1, s21_not_equal_0);
  tcase_add_test(tc1_1, s21_not_equal_1);
  tcase_add_test(tc1_1, s21_not_equal_2);
  tcase_add_test(tc1_1, s21_not_equal_3);
  tcase_add_test(tc1_1, s21_not_equal_4);
  tcase_add_test(tc1_1, s21_not_equal_5);
  tcase_add_test(tc1_1, s21_not_equal_6);
  tcase_add_test(tc1_1, s21_not_equal_7);
  tcase_add_test(tc1_1, s21_not_equal_8);
  tcase_add_test(tc1_1, s21_not_equal_9);

  return s;
}

int test_comparison() {
  int no_failed = 0;
  Suite *s;
  SRunner *sr;

  s = s21_comparison_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  no_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return no_failed;
}