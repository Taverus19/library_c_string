#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main_test_unit.h"
#include "s21_string.h"

#define BUF_SIZE 1024

static int g_test_id = 1;

#define ASSERT_SPRINTF_EQUAL(fmt, ...)                                     \
  do {                                                                     \
    char expected[BUF_SIZE] = {0};                                         \
    char actual[BUF_SIZE] = {0};                                           \
    int ret1 = sprintf(expected, fmt, __VA_ARGS__);                        \
    int ret2 = s21_sprintf(actual, fmt, __VA_ARGS__);                      \
    int ok = (ret1 == ret2);                                               \
    double val1 = 0.0, val2 = 0.0;                                         \
                                                                           \
    if (strchr(fmt, 'e') || strchr(fmt, 'E')) {                            \
      if (sscanf(expected, "%lf", &val1) != 1) val1 = 0.0;                 \
      if (sscanf(actual, "%lf", &val2) != 1) val2 = 0.0;                   \
      ok = ok && (fabs(val1 - val2) < 1e-6);                               \
    } else {                                                               \
      ok = ok && (strcmp(expected, actual) == 0);                          \
    }                                                                      \
                                                                           \
    const char *GREEN = "\033[32m";                                        \
    const char *RED = "\033[31m";                                          \
    const char *RESET = "\033[0m";                                         \
                                                                           \
    printf("%s[%02d] \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, expected, \
           RESET);                                                         \
                                                                           \
    if (!ok) {                                                             \
      printf(                                                              \
          "      expected: \"%s\" (len=%d)\n"                              \
          "      actual  : \"%s\" (len=%d)\n",                             \
          expected, ret1, actual, ret2);                                   \
    }                                                                      \
    fflush(stdout);                                                        \
                                                                           \
    ck_assert_int_eq(ret1, ret2);                                          \
    if (strchr(fmt, 'e') || strchr(fmt, 'E')) {                            \
      ck_assert_double_eq_tol(val1, val2, 1e-6);                           \
    } else {                                                               \
      ck_assert_str_eq(expected, actual);                                  \
    }                                                                      \
  } while (0)

START_TEST(t001_char) { ASSERT_SPRINTF_EQUAL("Char: %c", 'A'); }
END_TEST
START_TEST(t002_int) { ASSERT_SPRINTF_EQUAL("Int: %d", -12345); }
END_TEST
START_TEST(t003_float) { ASSERT_SPRINTF_EQUAL("Float: %f", 123.456); }
END_TEST
START_TEST(t004_string) { ASSERT_SPRINTF_EQUAL("String: %s", "Hello"); }
END_TEST
START_TEST(t005_unsigned) { ASSERT_SPRINTF_EQUAL("Unsigned: %u", 4294967295U); }
END_TEST
START_TEST(t006_percent) { ASSERT_SPRINTF_EQUAL("Percent: %c = %%", '%'); }
END_TEST
START_TEST(t007_i) { ASSERT_SPRINTF_EQUAL("Unsigned: %i", 123456); }
END_TEST

START_TEST(t007_e) { ASSERT_SPRINTF_EQUAL("Scientific (e): %e", 12345.678); }
END_TEST
START_TEST(t008_E) { ASSERT_SPRINTF_EQUAL("Scientific (E): %E", 12345.678); }
END_TEST
START_TEST(t009_g) { ASSERT_SPRINTF_EQUAL("Shortest (g): %g", 12345.678); }
END_TEST
START_TEST(t010_G) { ASSERT_SPRINTF_EQUAL("Shortest (G): %G", 12345.678); }
END_TEST

START_TEST(t011_hex_l) { ASSERT_SPRINTF_EQUAL("Hex lower: %x", 0xFFEE); }
END_TEST
START_TEST(t012_hex_u) { ASSERT_SPRINTF_EQUAL("Hex upper: %X", 0xFFEE); }
END_TEST
START_TEST(t013_octal) { ASSERT_SPRINTF_EQUAL("Octal: %o", 0777); }
END_TEST
START_TEST(t014_ptr) {
  int x = 0;
  ASSERT_SPRINTF_EQUAL("Pointer: %p", (void *)&x);
}
END_TEST
START_TEST(t015_ptr) { ASSERT_SPRINTF_EQUAL("Pointer: %10p", NULL); }
END_TEST

START_TEST(t016_ptr) { ASSERT_SPRINTF_EQUAL("Pointer: %p", NULL); }
END_TEST

START_TEST(t017_ptr) {
  int x = 42;
  ASSERT_SPRINTF_EQUAL("Pointer: %p", (void *)&x);
}
END_TEST

END_TEST
START_TEST(t018_ptr) { ASSERT_SPRINTF_EQUAL("Pointer: %-10p", NULL); }
END_TEST

START_TEST(t015_plus) { ASSERT_SPRINTF_EQUAL("Plus: %+d", 123); }
END_TEST
START_TEST(t016_minus) { ASSERT_SPRINTF_EQUAL("Minus: %-6d!", 123); }
END_TEST
START_TEST(t017_space) { ASSERT_SPRINTF_EQUAL("Space: % d", 123); }
END_TEST
START_TEST(t018_zero) { ASSERT_SPRINTF_EQUAL("Zero pad: %05d", 42); }
END_TEST
START_TEST(t019_sharp_x) { ASSERT_SPRINTF_EQUAL("Sharp hex: %#x", 255); }
END_TEST
START_TEST(t020_sharp_X) { ASSERT_SPRINTF_EQUAL("Sharp HEX: %#X", 255); }
END_TEST
START_TEST(t021_sharp_o) { ASSERT_SPRINTF_EQUAL("Sharp oct: %#o", 10); }
END_TEST
START_TEST(t022_sharp_f) { ASSERT_SPRINTF_EQUAL("Sharp float: %#f", 3.14); }
END_TEST

START_TEST(t023_w_num) { ASSERT_SPRINTF_EQUAL("Width: %10d", 123); }
END_TEST
START_TEST(t024_w_ast) { ASSERT_SPRINTF_EQUAL("Width *: %*d", 8, 123); }
END_TEST
START_TEST(t025_w_both) { ASSERT_SPRINTF_EQUAL("Both: %*.*f", 10, 3, 3.14159); }
END_TEST

START_TEST(t026_prec_i) { ASSERT_SPRINTF_EQUAL("Prec int: %.5d", 42); }
END_TEST
START_TEST(t027_prec_s) { ASSERT_SPRINTF_EQUAL("Prec str: %.3s", "abcdef"); }
END_TEST
START_TEST(t028_prec_f) { ASSERT_SPRINTF_EQUAL("Prec float: %.4f", 3.1415926); }
END_TEST
START_TEST(t029_prec_ast) {
  ASSERT_SPRINTF_EQUAL("Prec *: %.*f", 2, 3.1415926);
}
END_TEST

START_TEST(t030_len_h) {
  short h = -123;
  ASSERT_SPRINTF_EQUAL("Short: %hd", h);
}
END_TEST

START_TEST(t031_len_l) {
  long l = 123456789L;
  ASSERT_SPRINTF_EQUAL("Long: %ld", l);
}
END_TEST
START_TEST(t032_len_lu) {
  ASSERT_SPRINTF_EQUAL("Long Unsigned: %lu", ULONG_MAX);
}
END_TEST
START_TEST(t032_len_hu) { ASSERT_SPRINTF_EQUAL("Short Unsigned: %hu", 12345); }
END_TEST
START_TEST(t033_len_L) {
  long double L = 3.141592653589793238L;
  ASSERT_SPRINTF_EQUAL("Long double: %Lf", L);
}
END_TEST

START_TEST(t034_intmax) { ASSERT_SPRINTF_EQUAL("INT_MAX: %d", INT_MAX); }
END_TEST
START_TEST(t035_intmin) { ASSERT_SPRINTF_EQUAL("INT_MIN: %d", INT_MIN); }
END_TEST
START_TEST(t036_uintmax) { ASSERT_SPRINTF_EQUAL("UINT_MAX: %u", UINT_MAX); }
END_TEST
START_TEST(t037_zero) { ASSERT_SPRINTF_EQUAL("Zero: %d", 0); }
END_TEST
START_TEST(t038_nzero) { ASSERT_SPRINTF_EQUAL("Negative zero: %f", -0.0); }
END_TEST
START_TEST(t039_pzero) { ASSERT_SPRINTF_EQUAL("Positive zero: %f", +0.0); }
END_TEST
START_TEST(t040_pos_inf) { ASSERT_SPRINTF_EQUAL("INF: %f", INFINITY); }
END_TEST
START_TEST(t041_neg_inf) { ASSERT_SPRINTF_EQUAL("-INF: %f", -INFINITY); }
END_TEST
START_TEST(t042_nan) { ASSERT_SPRINTF_EQUAL("NAN: %f", NAN); }
END_TEST

START_TEST(t043_c1) { ASSERT_SPRINTF_EQUAL("|%+10.5d|", 123); }
END_TEST
START_TEST(t044_c2) { ASSERT_SPRINTF_EQUAL("|%-#12.6x|", 3735928559U); }
END_TEST
START_TEST(t045_c3) { ASSERT_SPRINTF_EQUAL("|%#08o|", 64); }
END_TEST
START_TEST(t046_c4) { ASSERT_SPRINTF_EQUAL("|%+8.3f|", 3.14); }
END_TEST
START_TEST(t047_c5) { ASSERT_SPRINTF_EQUAL("|%0+8.2f|", 123.456); }
END_TEST
START_TEST(t048_c6) { ASSERT_SPRINTF_EQUAL("|%-#14.4g|", 12345.6789); }
END_TEST

START_TEST(t049_empty) { ASSERT_SPRINTF_EQUAL("Empty: '%s'", ""); }
END_TEST
START_TEST(t050_nullp) { ASSERT_SPRINTF_EQUAL("Null ptr: %p", NULL); }
END_TEST

START_TEST(t221_sprintf_float_space) { ASSERT_SPRINTF_EQUAL("% f", 3.14); }
END_TEST

START_TEST(t222_sprintf_float_negative) { ASSERT_SPRINTF_EQUAL("%f", -3.14); }
END_TEST

START_TEST(t224_sprintf_exp_overflow) { ASSERT_SPRINTF_EQUAL("%e", 9.9999999); }
END_TEST

START_TEST(t228_sprintf_float_str_negative) {
  ASSERT_SPRINTF_EQUAL("%.3f", -123.456);
}
END_TEST

START_TEST(t229_sprintf_buffer_overflow) {
  ASSERT_SPRINTF_EQUAL("%.10s",
                       "This is a very long string that should be truncated");
}
END_TEST

START_TEST(t230_sprintf_inf_plus) { ASSERT_SPRINTF_EQUAL("%+f", INFINITY); }
END_TEST

START_TEST(t231_sprintf_inf_space) { ASSERT_SPRINTF_EQUAL("% f", INFINITY); }
END_TEST

START_TEST(t232_sprintf_signed_zero) { ASSERT_SPRINTF_EQUAL("%f", -0.0); }
END_TEST

START_TEST(t233_sprintf_long_float) {
  ASSERT_SPRINTF_EQUAL("%.6f", 123456789.123456789);
}
END_TEST

START_TEST(t234_sprintf_float_max_precision) {
  ASSERT_SPRINTF_EQUAL("%.6f", 1.23456789);
}
END_TEST

START_TEST(t235_sprintf_float_zero_pad) { ASSERT_SPRINTF_EQUAL("%07f", 3.14); }
END_TEST

START_TEST(t236_sprintf_float_to_str_negative) {
  ASSERT_SPRINTF_EQUAL("%f", -123.456);
  ASSERT_SPRINTF_EQUAL("%f", -0.0);
  ASSERT_SPRINTF_EQUAL("%.0f", -123.456);
  ASSERT_SPRINTF_EQUAL("%.10f", -123.456);
  ASSERT_SPRINTF_EQUAL("%f", -0.000000123);
  ASSERT_SPRINTF_EQUAL("%10f", -123.456);
  ASSERT_SPRINTF_EQUAL("%015f", -123.456);
}
END_TEST

START_TEST(t237_sprintf_float_to_str_edge_cases) {
  ASSERT_SPRINTF_EQUAL("%.0f", -0.0);
  ASSERT_SPRINTF_EQUAL("%.5f", -0.0);
  ASSERT_SPRINTF_EQUAL("%.10f", -0.0000000001);
  ASSERT_SPRINTF_EQUAL("%.1f", -3.85);
  ASSERT_SPRINTF_EQUAL("%.3f", -0.123);
  ASSERT_SPRINTF_EQUAL("%15.2f", -123.45);
  ASSERT_SPRINTF_EQUAL("%-15.2f", -123.45);
  ASSERT_SPRINTF_EQUAL("%+.2f", -123.45);
}
END_TEST

START_TEST(t238_sprintf_float_to_str_flags) {
  ASSERT_SPRINTF_EQUAL("% f", -123.456);
  ASSERT_SPRINTF_EQUAL("%010f", -123.456);
  ASSERT_SPRINTF_EQUAL("%-10f", -123.456);
  ASSERT_SPRINTF_EQUAL("%#.0f", -123.456);
  ASSERT_SPRINTF_EQUAL("%+#015.3f", -123.456);
}
END_TEST

START_TEST(t240_sprintf_buffer_overflow_add_str) {
  ASSERT_SPRINTF_EQUAL("%.20s",
                       "This is a very long string that will definitely cause "
                       "buffer overflow in small buffers");
  ASSERT_SPRINTF_EQUAL("%.15s%.15s", "First long string", "Second long string");
  ASSERT_SPRINTF_EQUAL("%50.30s",
                       "Testing buffer overflow with width and precision");
  ASSERT_SPRINTF_EQUAL("%-30.20s", "Left-aligned overflow test string");
  ASSERT_SPRINTF_EQUAL("%*.*s", 30, 25,
                       "Dynamic width and precision overflow test");
}
END_TEST

START_TEST(t223_sprintf_exp_small) {
  char str1[100], str2[100];
  double value = 0.0000123;
  sprintf(str1, "%e", value);
  s21_sprintf(str2, "%e", value);
  double val1, val2;
  sscanf(str1, "%lf", &val1);
  sscanf(str2, "%lf", &val2);
  ck_assert_double_eq_tol(val1, val2, 1e-7);
}
END_TEST

START_TEST(t225_sprintf_exp_negative) {
  char str1[100], str2[100];
  double value = -1.23;
  sprintf(str1, "%e", value);
  s21_sprintf(str2, "%e", value);
  double val1, val2;
  sscanf(str1, "%lf", &val1);
  sscanf(str2, "%lf", &val2);
  ck_assert_double_eq_tol(val1, val2, 1e-6);
}
END_TEST

START_TEST(t226_sprintf_exp_plus) {
  char str1[100], str2[100];
  double value = 1.23;
  sprintf(str1, "%+e", value);
  s21_sprintf(str2, "%+e", value);
  double val1, val2;
  sscanf(str1, "%lf", &val1);
  sscanf(str2, "%lf", &val2);
  ck_assert_double_eq_tol(val1, val2, 1e-6);
}
END_TEST

START_TEST(t227_sprintf_exp_space) {
  char str1[100], str2[100];
  double value = 1.23;
  sprintf(str1, "% e", value);
  s21_sprintf(str2, "% e", value);
  double val1, val2;
  sscanf(str1, "%lf", &val1);
  sscanf(str2, "%lf", &val2);
  ck_assert_double_eq_tol(val1, val2, 1e-6);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("all");

#define ADD(t) tcase_add_test(tc, t)
  ADD(t001_char);
  ADD(t002_int);
  ADD(t003_float);
  ADD(t004_string);
  ADD(t005_unsigned);
  ADD(t006_percent);
  ADD(t007_i);
  ADD(t007_e);
  ADD(t008_E);
  ADD(t009_g);
  ADD(t010_G);
  ADD(t011_hex_l);
  ADD(t012_hex_u);
  ADD(t013_octal);
  ADD(t014_ptr);
  ADD(t015_ptr);
  ADD(t016_ptr);
  ADD(t017_ptr);
  ADD(t018_ptr);
  ADD(t015_plus);
  ADD(t016_minus);
  ADD(t017_space);
  ADD(t018_zero);
  ADD(t019_sharp_x);
  ADD(t020_sharp_X);
  ADD(t021_sharp_o);
  ADD(t022_sharp_f);
  ADD(t023_w_num);
  ADD(t024_w_ast);
  ADD(t025_w_both);
  ADD(t026_prec_i);
  ADD(t027_prec_s);
  ADD(t028_prec_f);
  ADD(t029_prec_ast);
  ADD(t030_len_h);
  ADD(t031_len_l);
  ADD(t032_len_lu);
  ADD(t032_len_hu);
  ADD(t033_len_L);
  ADD(t034_intmax);
  ADD(t035_intmin);
  ADD(t036_uintmax);
  ADD(t037_zero);
  ADD(t038_nzero);
  ADD(t039_pzero);
  ADD(t040_pos_inf);
  ADD(t041_neg_inf);
  ADD(t042_nan);
  ADD(t043_c1);
  ADD(t044_c2);
  ADD(t045_c3);
  ADD(t046_c4);
  ADD(t047_c5);
  ADD(t048_c6);
  ADD(t049_empty);
  ADD(t050_nullp);
  ADD(t221_sprintf_float_space);
  ADD(t222_sprintf_float_negative);
  ADD(t223_sprintf_exp_small);
  ADD(t224_sprintf_exp_overflow);
  ADD(t225_sprintf_exp_negative);
  ADD(t226_sprintf_exp_plus);
  ADD(t227_sprintf_exp_space);
  ADD(t228_sprintf_float_str_negative);
  ADD(t229_sprintf_buffer_overflow);
  ADD(t230_sprintf_inf_plus);
  ADD(t231_sprintf_inf_space);
  ADD(t232_sprintf_signed_zero);
  ADD(t233_sprintf_long_float);
  ADD(t234_sprintf_float_max_precision);
  ADD(t235_sprintf_float_zero_pad);
  ADD(t236_sprintf_float_to_str_negative);
  ADD(t237_sprintf_float_to_str_edge_cases);
  ADD(t238_sprintf_float_to_str_flags);
  ADD(t240_sprintf_buffer_overflow_add_str);
#undef ADD

  suite_add_tcase(s, tc);
  return s;
}
