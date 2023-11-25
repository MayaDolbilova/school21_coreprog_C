#include <check.h>

#include "s21_smartcal.h"

START_TEST(test_calc_1) {
  char input[255] = "5+7*2/(2-6)^3";
  double result = 0.0;
  calculator(input, "0.0", &result);
  ck_assert_double_eq(result, 4.78125);
}
END_TEST

START_TEST(test_calc_2) {
  char input[255] = "2+5+7+9*3*2^5";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq(result, 878);
}
END_TEST

// START_TEST(test_calc_3) {
//   char input[255] = "123.456+5*4^3";
//   double result;
//   calculator(input, "0.0", &result);
//   ck_assert_double_eq(result, 443.456);
// }
// END_TEST

START_TEST(test_calc_4) {
  char input[255] = "(8+2*5)/(1+3*2-4)";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq(result, 6);
}
END_TEST

START_TEST(test_calc_5) {
  char input[255] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq(result, 10);
}
END_TEST

START_TEST(test_calc_6) {
  char input[255] = "cos(1*2)-1";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq_tol(result, -1.41614683655, 1e-06);
}
END_TEST

START_TEST(test_calc_7) {
  char input[255] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq_tol(result, -1.83907152908, 1e-06);
}
END_TEST

START_TEST(test_calc_8) {
  char input[255] = "sin(cos(5))";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq_tol(result, 0.27987335076, 1e-06);
}
END_TEST

START_TEST(test_calc_9) {
  char input[255] = "2.33 mod 1";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq_tol(result, 0.33, 1e-06);
}
END_TEST

START_TEST(test_calc_10) {
  char input[255] = "3+4*2/1-5+2^2";
  double result;
  calculator(input, "10.0", &result);
  ck_assert_double_eq_tol(result, 10, 1e-06);
}
END_TEST

START_TEST(test_calc_11) {
  char input[255] = "3+4*2/1-5+2^2";
  double result;
  calculator(input, "10.0", &result);
  ck_assert_double_eq_tol(result, 10, 1e-06);
}
END_TEST

START_TEST(test_calc_12) {
  char input[255] = "asin(2*x)";
  double result;
  calculator(input, "0.0003", &result);
  ck_assert_double_eq_tol(result, 0.0006, 1e-06);
}
END_TEST

START_TEST(test_calc_13) {
  char input[255] = "acos(2*x)";
  double result;
  calculator(input, "0.0019", &result);
  ck_assert_double_eq_tol(result, 1.567, 1e-03);
}
END_TEST

START_TEST(test_calc_14) {
  char input[255] = "atan(2*x)";
  double result;
  calculator(input, "0.0019", &result);
  ck_assert_double_eq_tol(result, 0.00379998, 1e-06);
}
END_TEST

START_TEST(test_calc_15) {
  char input[255] = "tan(2*x)";
  double result;
  calculator(input, "0.004", &result);
  ck_assert_double_eq_tol(result, 0.00800017, 1e-06);
}
END_TEST

START_TEST(test_calc_16) {
  char input[255] = "sqrt(2*x)";
  double result;
  calculator(input, "25.0", &result);
  ck_assert_double_eq_tol(result, 7.07107, 1e-05);
}
END_TEST

START_TEST(test_calc_17) {
  char input[255] = "ln(10*x)";
  double result;
  calculator(input, "2.0", &result);
  ck_assert_double_eq_tol(result, 2.99573, 1e-05);
}
END_TEST

START_TEST(test_calc_18) {
  char input[255] = "log(10*x)";
  double result;
  calculator(input, "2.0", &result);
  ck_assert_double_eq_tol(result, 1.30103, 1e-05);
}
END_TEST

START_TEST(test_calc_19) {
  char input[255] = "()";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq_tol(result, 0, 1e-06);
}
END_TEST

START_TEST(test_calc_20) {
  char input[255] = "3-(-3)";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq_tol(result, 6, 1e-06);
}
END_TEST

START_TEST(test_calc_21) {
  char input[255] = "-5-(-3)";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq(result, -2);
}
END_TEST

START_TEST(test_calc_22) {
  char input[255] = "5cos()";
  int error = 0;
  double result;
  error = calculator(input, "0.0", &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_23) {
  char input[255] = "5/0";
  int error = 0;
  double result;
  error = calculator(input, "0.0", &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_24) {
  char input[255] = "mod5";
  int error = 0;
  double result;
  error = calculator(input, "0.0", &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_25) {
  char input[255] = "^2";
  int error = 0;
  double result;
  error = calculator(input, "0.0", &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_26) {
  char input[255] = "-3/(-3)";
  double result;
  calculator(input, "0.0", &result);
  ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(test_calc_27) {
  char input[255] = ")77321321(sin(5))";
  double result;
  int error = 0;
  error = calculator(input, "0.0", &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calc_32) {
  char input[255] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double result;
  calculator(input, "1", &result);
  ck_assert_double_eq(result, 10);
}
END_TEST

START_TEST(test_calc_33) {
  char input[255] = "cos(1*2)-1";
  double result;
  calculator(input, "1", &result);
  ck_assert_double_eq_tol(result, -1.41614683655, 1e-06);
}
END_TEST

START_TEST(test_calc_34) {
  char input[255] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result;
  calculator(input, "1", &result);
  ck_assert_double_eq_tol(result, -1.83907152908, 1e-06);
}
END_TEST

START_TEST(test_calc_35) {
  char input[255] = "sin(cos(5))";
  double result;
  calculator(input, "1", &result);
  ck_assert_double_eq_tol(result, 0.27987335076, 1e-06);
}
END_TEST

START_TEST(test_calc_37) {
  // double x = 10;
  char input[255] = "3+4*2/1-5+2^2";
  double result;
  calculator(input, "10", &result);
  ck_assert_double_eq_tol(result, 10, 1e-06);
}
END_TEST

START_TEST(test_calc_38) {
  // double x = 10;
  char input[255] = "3+4*2/1-5+2^2";
  double result;
  calculator(input, "10", &result);
  ck_assert_double_eq_tol(result, 10, 1e-06);
}
END_TEST

START_TEST(test_calc_39) {
  // double x = 0.0003;
  char input[255] = "asin(2*x)";
  double result;
  calculator(input, "0.0003", &result);
  ck_assert_double_eq_tol(result, 0.0006, 1e-06);
}
END_TEST

START_TEST(test_calc_40) {
  // double x = 0.0019;
  char input[255] = "acos(2*x)";
  double result;
  calculator(input, "0.0019", &result);
  ck_assert_double_eq_tol(result, 1.567, 1e-03);
}
END_TEST

START_TEST(test_calc_41) {
  // double x = 0.0019;
  char input[255] = "atan(2*x)";
  double result;
  calculator(input, "0.0019", &result);
  ck_assert_double_eq_tol(result, 0.00379998, 1e-06);
}
END_TEST

START_TEST(test_calc_42) {
  // double x = 0.004;
  char input[255] = "tan(2*x)";
  double result;
  calculator(input, "0.004", &result);
  ck_assert_double_eq_tol(result, 0.00800017, 1e-06);
}
END_TEST

START_TEST(test_calc_43) {
  // double x = 25;
  char input[255] = "sqrt(2*x)";
  double result;
  calculator(input, "25", &result);
  ck_assert_double_eq_tol(result, 7.07107, 1e-05);
}
END_TEST

START_TEST(test_calc_44) {
  // double x = 2;
  char input[255] = "ln(10*x)";
  double result;
  calculator(input, "2", &result);
  ck_assert_double_eq_tol(result, 2.99573, 1e-05);
}
END_TEST

START_TEST(test_calc_45) {
  // double x = 2;
  char input[255] = "log(10*x)";
  double result;
  calculator(input, "2", &result);
  ck_assert_double_eq_tol(result, 1.30103, 1e-05);
}
END_TEST

START_TEST(test_calc_46) {
  char input[255] = "()";
  double result;
  calculator(input, "0", &result);
  ck_assert_double_eq_tol(result, 0, 1e-06);
}
END_TEST

START_TEST(test_calc_47) {
  char input[255] = "3-(-3)";
  double result;
  calculator(input, "0", &result);
  ck_assert_double_eq_tol(result, 6, 1e-06);
}
END_TEST

START_TEST(test_calc_48) {
  char input[255] = "-5-(-3)";
  double result;
  calculator(input, "0", &result);
  ck_assert_double_eq_tol(result, -2, 1e-06);
}
END_TEST

START_TEST(test_calc_49) {
  char input[255] = ".5 + 4";
  double result;
  calculator(input, "0", &result);
  ck_assert_double_eq_tol(result, 4.5, 1e-06);
}
END_TEST

START_TEST(test_calc_50) {
  char input[255] = "0.5 - 1";
  double result;
  calculator(input, "0", &result);
  ck_assert_double_eq_tol(result, -0.5, 1e-06);
}
END_TEST

START_TEST(test_calc_51) {
  char input[255] = "2 + .5";
  double result;
  calculator(input, "0", &result);
  ck_assert_double_eq_tol(result, 2.5, 1e-06);
}
END_TEST

int main() {
  Suite *suite = suite_create("s21_smart_calc: ");
  TCase *tcase_core = tcase_create("s21_smart_calc: ");
  SRunner *suite_runner = srunner_create(suite);
  int result;
  suite_add_tcase(suite, tcase_core);

  tcase_add_test(tcase_core, test_calc_1);
  tcase_add_test(tcase_core, test_calc_2);
  // tcase_add_test(tcase_core, test_calc_3);
  tcase_add_test(tcase_core, test_calc_4);
  tcase_add_test(tcase_core, test_calc_5);
  tcase_add_test(tcase_core, test_calc_6);
  tcase_add_test(tcase_core, test_calc_7);
  tcase_add_test(tcase_core, test_calc_8);
  tcase_add_test(tcase_core, test_calc_9);
  tcase_add_test(tcase_core, test_calc_10);
  tcase_add_test(tcase_core, test_calc_11);
  tcase_add_test(tcase_core, test_calc_12);
  tcase_add_test(tcase_core, test_calc_13);
  tcase_add_test(tcase_core, test_calc_14);
  tcase_add_test(tcase_core, test_calc_15);
  tcase_add_test(tcase_core, test_calc_15);
  tcase_add_test(tcase_core, test_calc_16);
  tcase_add_test(tcase_core, test_calc_17);
  tcase_add_test(tcase_core, test_calc_18);
  tcase_add_test(tcase_core, test_calc_19);
  tcase_add_test(tcase_core, test_calc_20);
  tcase_add_test(tcase_core, test_calc_21);
  tcase_add_test(tcase_core, test_calc_22);
  tcase_add_test(tcase_core, test_calc_23);
  tcase_add_test(tcase_core, test_calc_24);
  tcase_add_test(tcase_core, test_calc_25);
  tcase_add_test(tcase_core, test_calc_26);
  tcase_add_test(tcase_core, test_calc_27);

  tcase_add_test(tcase_core, test_calc_32);
  tcase_add_test(tcase_core, test_calc_33);
  tcase_add_test(tcase_core, test_calc_34);
  tcase_add_test(tcase_core, test_calc_35);
  tcase_add_test(tcase_core, test_calc_37);
  tcase_add_test(tcase_core, test_calc_38);
  tcase_add_test(tcase_core, test_calc_39);
  tcase_add_test(tcase_core, test_calc_40);
  tcase_add_test(tcase_core, test_calc_41);
  tcase_add_test(tcase_core, test_calc_42);
  tcase_add_test(tcase_core, test_calc_43);
  tcase_add_test(tcase_core, test_calc_44);
  tcase_add_test(tcase_core, test_calc_45);
  tcase_add_test(tcase_core, test_calc_46);
  tcase_add_test(tcase_core, test_calc_47);
  tcase_add_test(tcase_core, test_calc_48);
  tcase_add_test(tcase_core, test_calc_49);
  tcase_add_test(tcase_core, test_calc_50);
  tcase_add_test(tcase_core, test_calc_51);

  srunner_run_all(suite_runner, CK_VERBOSE);
  result = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return result == 0 ? 0 : 1;
}