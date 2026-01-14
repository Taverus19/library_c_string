#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main_test_unit.h"
#include "s21_sscanf.h"
#include "s21_string.h"

#define BUF_SIZE 1024

static int g_test_id = 1;

#define ASSERT_SSCANF_EQUAL(str, fmt, arg1, arg2)                            \
  do {                                                                       \
    int ret1 = sscanf(str, fmt, arg1);                                       \
    int ret2 = s21_sscanf(str, fmt, arg2);                                   \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

#define ASSERT_SSCANF_EQUAL3(str, fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
  do {                                                                       \
    int ret1 = sscanf(str, fmt, arg1, arg2, arg3);                           \
    int ret2 = s21_sscanf(str, fmt, arg4, arg5, arg6);                       \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

#define ASSERT_SSCANF_EQUAL_NOARG(str, fmt)                                  \
  do {                                                                       \
    int ret1 = sscanf(str, fmt);                                             \
    int ret2 = s21_sscanf(str, fmt);                                         \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

#define ASSERT_SSCANF_EQUAL2(str, fmt, arg1, arg2)                           \
  do {                                                                       \
    int ret1 = sscanf(str, fmt, arg1);                                       \
    int ret2 = s21_sscanf(str, fmt, arg2);                                   \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

#define ASSERT_SSCANF_EQUAL4(str, fmt, arg1, arg2, arg3, arg4)               \
  do {                                                                       \
    int ret1 = sscanf(str, fmt, arg1, arg2);                                 \
    int ret2 = s21_sscanf(str, fmt, arg3, arg4);                             \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

#define ASSERT_SSCANF_EQUAL6(str, fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
  do {                                                                       \
    int ret1 = sscanf(str, fmt, arg1, arg2, arg3);                           \
    int ret2 = s21_sscanf(str, fmt, arg4, arg5, arg6);                       \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

#define ASSERT_SSCANF_EQUAL8(str, fmt, arg1, arg2, arg3, arg4, arg5, arg6,   \
                             arg7, arg8)                                     \
  do {                                                                       \
    int ret1 = sscanf(str, fmt, arg1, arg2, arg3, arg4);                     \
    int ret2 = s21_sscanf(str, fmt, arg5, arg6, arg7, arg8);                 \
    int ok = (ret1 == ret2);                                                 \
                                                                             \
    const char *GREEN = "\033[32m";                                          \
    const char *RED = "\033[31m";                                            \
    const char *RESET = "\033[0m";                                           \
                                                                             \
    printf("%s[%02d] \"%s\" with \"%s\"%s\n", ok ? GREEN : RED, g_test_id++, \
           str, fmt, RESET);                                                 \
                                                                             \
    if (!ok) {                                                               \
      printf(                                                                \
          "      expected return: %d\n"                                      \
          "      actual return  : %d\n",                                     \
          ret1, ret2);                                                       \
    }                                                                        \
    ck_assert_int_eq(ret1, ret2);                                            \
  } while (0)

START_TEST(t001_char) {
  char c1, c2;
  ASSERT_SSCANF_EQUAL("A", "%c", &c1, &c2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t002_decimal) {
  int d1, d2;
  ASSERT_SSCANF_EQUAL("-12345", "%d", &d1, &d2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t003_float) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("123.456", "%lf", &f1, &f2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(t004_string) {
  char s1[100], s2[100];
  ASSERT_SSCANF_EQUAL("Hello", "%s", s1, s2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(t005_exp_lower) {
  double e1, e2;
  ASSERT_SSCANF_EQUAL("1.23e-4", "%le", &e1, &e2);
  ck_assert_float_eq(e1, e2);
}
END_TEST

START_TEST(t006_exp_upper) {
  double E1, E2;
  ASSERT_SSCANF_EQUAL("1.23E+4", "%lE", &E1, &E2);
  ck_assert_float_eq(E1, E2);
}
END_TEST

START_TEST(t007_g_auto) {
  double g1, g2;
  ASSERT_SSCANF_EQUAL("0.0001", "%lg", &g1, &g2);
  ck_assert_float_eq(g1, g2);
}
END_TEST

START_TEST(t008_G_auto) {
  double G1, G2;
  ASSERT_SSCANF_EQUAL("1E6", "%lG", &G1, &G2);
  ck_assert_float_eq(G1, G2);
}
END_TEST

START_TEST(t009_hex_lower) {
  unsigned x1, x2;
  ASSERT_SSCANF_EQUAL("0xffee", "%x", &x1, &x2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(t010_hex_upper) {
  unsigned X1, X2;
  ASSERT_SSCANF_EQUAL("0XFFEE", "%X", &X1, &X2);
  ck_assert_uint_eq(X1, X2);
}
END_TEST

START_TEST(t011_octal) {
  unsigned o1, o2;
  ASSERT_SSCANF_EQUAL("0777", "%o", &o1, &o2);
  ck_assert_uint_eq(o1, o2);
}
END_TEST

START_TEST(t012_pointer) {
  void *p1, *p2;
  ASSERT_SSCANF_EQUAL("0x12345678", "%p", &p1, &p2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(t013_width_number) {
  char s1[100], s2[100];
  ASSERT_SSCANF_EQUAL("Hello World", "%5s", s1, s2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(t014_width_asterisk) { ASSERT_SSCANF_EQUAL_NOARG("Hello", "%*s"); }
END_TEST

START_TEST(t017_short) {
  short h1, h2;
  ASSERT_SSCANF_EQUAL("-123", "%hd", &h1, &h2);
  ck_assert_int_eq(h1, h2);
}
END_TEST

START_TEST(t018_long) {
  long l1, l2;
  ASSERT_SSCANF_EQUAL("123456789", "%ld", &l1, &l2);
  ck_assert_int_eq(l1, l2);
}
END_TEST

START_TEST(t019_long_double) {
  long double L1 = 0, L2 = 0;
  int ret1 = sscanf("3.14159", "%Lf", &L1);
  int ret2 = s21_sscanf("3.14159", "%Lf", &L2);
  ck_assert_int_eq(ret1, ret2);
  long double diff = fabsl(L1 - L2);
  long double epsilon = 1e-5L;
  ck_assert(diff < epsilon);
}
END_TEST

START_TEST(t020_combined) {
  int i1, i2;
  double f1, f2;
  char s1[100], s2[100];
  ASSERT_SSCANF_EQUAL3("42 3.14 Hello", "%d %lf %s", &i1, &f1, s1, &i2, &f2,
                       s2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq(f1, f2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(t021_empty) {
  char s1[100], s2[100];
  ASSERT_SSCANF_EQUAL("", "%s", s1, s2);
}
END_TEST

START_TEST(t022_whitespace) {
  int i1, i2;
  ASSERT_SSCANF_EQUAL("   42", "%d", &i1, &i2);
  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(t023_max_values) {
  int i1, i2;
  ASSERT_SSCANF_EQUAL("2147483647", "%d", &i1, &i2);
  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(t024_min_values) {
  int i1, i2;
  ASSERT_SSCANF_EQUAL("-2147483648", "%d", &i1, &i2);
  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(t031_only_spaces_input) {
  int x1, x2;
  ASSERT_SSCANF_EQUAL("    ", "%d", &x1, &x2);
}
END_TEST

START_TEST(t032_no_match) {
  int x1, x2;
  ASSERT_SSCANF_EQUAL("abc", "%d", &x1, &x2);
}
END_TEST

START_TEST(t033_overflow) {
  int x1, x2;
  ASSERT_SSCANF_EQUAL("999999999999999999999", "%d", &x1, &x2);
}
END_TEST

START_TEST(t035_mixed_hex) {
  unsigned long x1, x2;
  ASSERT_SSCANF_EQUAL("0xABcd", "%lx", &x1, &x2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(t037_negative_zero) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("-0.0", "%lf", &f1, &f2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(t026_combined_hex_dec) {
  int d1, d2;
  unsigned x1, x2;
  ASSERT_SSCANF_EQUAL4("42 0xFF", "%d %x", &d1, &x1, &d2, &x2);
  ck_assert_int_eq(d1, d2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(t027_n_basic) {
  int n1 = 0, n2 = 0;
  char c1, c2;
  ASSERT_SSCANF_EQUAL4("A", "%c%n", &c1, &n1, &c2, &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t030_empty_format) {
  char c1, c2;
  ASSERT_SSCANF_EQUAL2("Hello", " %c", &c1, &c2);
}
END_TEST

START_TEST(t034_multiple_spaces) {
  int x1, x2;
  double f1, f2;
  ASSERT_SSCANF_EQUAL4("42     3.14", "%d %lf", &x1, &f1, &x2, &f2);
  ck_assert_int_eq(x1, x2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(t036_zero_values) {
  int i1, i2;
  double f1, f2;
  ASSERT_SSCANF_EQUAL4("0 0.0", "%d %lf", &i1, &f1, &i2, &f2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(t038_mixed_separators) {
  int x1, x2, y1, y2;
  ASSERT_SSCANF_EQUAL4("1,2", "%d,%d", &x1, &y1, &x2, &y2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(y1, y2);
}
END_TEST

START_TEST(t039_consecutive_chars) {
  char c1[4], c2[4];
  ASSERT_SSCANF_EQUAL8("abcd", "%c%c%c%c", &c1[0], &c1[1], &c1[2], &c1[3],
                       &c2[0], &c2[1], &c2[2], &c2[3]);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(c1[i], c2[i]);
  }
}
END_TEST

START_TEST(t046_int_negative_width3) {
  int num1, num2;

  int ret1 = sscanf("-42", "%3d", &num1);
  int ret2 = s21_sscanf("-42", "%3d", &num2);

  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t045_int_width_spaces) {
  const char *input = "   100 29780";
  int a1, b1, a2, b2;

  int ret1 = sscanf(input, "%d %3d", &a1, &b1);
  int ret2 = s21_sscanf(input, "%d %3d", &a2, &b2);

  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(t047_int_positive_width2) {
  int num1, num2;

  int ret1 = sscanf("+99", "%2d", &num1);
  int ret2 = s21_sscanf("+99", "%2d", &num2);

  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t048_int_negative_width2) {
  int num1, num2;

  int ret1 = sscanf("-99", "%2d", &num1);
  int ret2 = s21_sscanf("-99", "%2d", &num2);

  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t049_int_empty_str) {
  int num1, num2;

  int ret1 = sscanf("", "%d", &num1);
  int ret2 = s21_sscanf("", "%d", &num2);

  ck_assert_int_eq(ret1, ret2);
}
END_TEST

START_TEST(t050_int_regular) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("123", "%d", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t051_int_negative) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("-456", "%d", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t052_int_positive_sign) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("+789", "%d", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t053_int_width_3) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("12345", "%3d", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t054_int_width_2) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("987654", "%2d", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t055_int_skip) { ASSERT_SSCANF_EQUAL_NOARG("123", "%*d"); }
END_TEST

START_TEST(t056_int_skip_width) { ASSERT_SSCANF_EQUAL_NOARG("123456", "%*2d"); }
END_TEST

START_TEST(t057_int_partial_invalid) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("+abc", "%d", &num1, &num2);
}
END_TEST

START_TEST(t058_int_mixed_input) {
  int a1, b1, a2, b2;
  ASSERT_SSCANF_EQUAL4("  -100  +29780", "%d %3d", &a1, &b1, &a2, &b2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(t059_int_overflow_positive) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("2147483648", "%d", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t060_short_int_max) {
  short sh1, sh2;
  ASSERT_SSCANF_EQUAL("32767", "%hd", &sh1, &sh2);
  ck_assert_int_eq(sh1, sh2);
}
END_TEST

START_TEST(t061_short_int_min) {
  short sh1, sh2;
  ASSERT_SSCANF_EQUAL("-32768", "%hd", &sh1, &sh2);
  ck_assert_int_eq(sh1, sh2);
}
END_TEST

START_TEST(t062_short_int_overflow_positive) {
  short sh1, sh2;
  ASSERT_SSCANF_EQUAL("32768", "%hd", &sh1, &sh2);
  ck_assert_int_eq(sh1, sh2);
}
END_TEST

START_TEST(t063_short_int_overflow_negative) {
  short sh1, sh2;
  ASSERT_SSCANF_EQUAL("-32769", "%hd", &sh1, &sh2);
  ck_assert_int_eq(sh1, sh2);
}
END_TEST

START_TEST(t064_unsigned_short_max) {
  unsigned short ush1, ush2;
  ASSERT_SSCANF_EQUAL("65535", "%hu", &ush1, &ush2);
  ck_assert_int_eq(ush1, ush2);
}
END_TEST

START_TEST(t065_unsigned_short_negative) {
  unsigned short ush1, ush2;
  ASSERT_SSCANF_EQUAL("-1", "%hu", &ush1, &ush2);
  ck_assert_int_eq(ush1, ush2);
}
END_TEST

START_TEST(t066_unsigned_short_overflow) {
  unsigned short ush1, ush2;
  ASSERT_SSCANF_EQUAL("65536", "%hu", &ush1, &ush2);
  ck_assert_int_eq(ush1, ush2);
}
END_TEST

START_TEST(t067_long_int_max) {
  long l1, l2;
  ASSERT_SSCANF_EQUAL("2147483647", "%ld", &l1, &l2);
  ck_assert_int_eq(l1, l2);
}
END_TEST

START_TEST(t068_long_int_min) {
  long l1, l2;
  ASSERT_SSCANF_EQUAL("-2147483648", "%ld", &l1, &l2);
  ck_assert_int_eq(l1, l2);
}
END_TEST

START_TEST(t069_long_int_overflow_positive) {
  long l1, l2;
  ASSERT_SSCANF_EQUAL("2147483648", "%ld", &l1, &l2);
  ck_assert_int_eq(l1, l2);
}
END_TEST

START_TEST(t070_long_int_overflow_negative) {
  long l1, l2;
  ASSERT_SSCANF_EQUAL("-2147483649", "%ld", &l1, &l2);
  ck_assert_int_eq(l1, l2);
}
END_TEST

START_TEST(t071_unsigned_long_max) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("4294967295", "%lu", &ul1, &ul2);
  ck_assert_int_eq(ul1, ul2);
}
END_TEST

START_TEST(t072_unsigned_long_negative) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("-1", "%lu", &ul1, &ul2);
  ck_assert_int_eq(ul1, ul2);
}
END_TEST

START_TEST(t073_unsigned_long_overflow) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("4294967296", "%lu", &ul1, &ul2);
  ck_assert_int_eq(ul1, ul2);
}
END_TEST

START_TEST(t074_mixed_short_and_long) {
  short sh1, sh2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL4(" -32768 4294967295 ", "%hd %lu", &sh1, &ul1, &sh2,
                       &ul2);
  ck_assert_int_eq(sh1, sh2);
  ck_assert_int_eq(ul1, ul2);
}
END_TEST

START_TEST(t075_mixed_long_overflow) {
  long l1, l2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL4(" 123456789012 -999999999999 ", "%ld %lu", &l1, &ul1,
                       &l2, &ul2);
  ck_assert_int_eq(l1, l2);
  ck_assert_int_eq(ul1, ul2);
}
END_TEST

START_TEST(t076_unsigned_long_empty_input) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("   ", "%lu", &ul1, &ul2);
}
END_TEST

START_TEST(t077_unsigned_long_empty_string) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("", "%lu", &ul1, &ul2);
}
END_TEST

START_TEST(t080_i_decimal) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("123", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t081_i_octal) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0123", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t082_i_hex_lower) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0x1a", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t083_i_hex_upper) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0XABC", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t084_i_negative_hex) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("   -0XABC", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t085_i_invalid_input) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("abc", "%i", &num1, &num2);
}
END_TEST

START_TEST(t086_i_only_spaces) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("   ", "%i", &num1, &num2);
}
END_TEST

START_TEST(t087_i_empty_string) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("", "%i", &num1, &num2);
}
END_TEST

START_TEST(t088_i_overflow_positive) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("2147483648", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t089_i_overflow_negative) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("-2147483649", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t090_i_mixed_success_failure) {
  int a1, a2, b1, b2;
  ASSERT_SSCANF_EQUAL4("123 abc", "%i %i", &a1, &b1, &a2, &b2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t091_i_width) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("1234567890", "%3i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t092_i_skip_asterisk) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0x1a 123", "%*i %i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t093_i_zero_values) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL4("0 -0", "%i %i", &num1, &num2, &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t094_i_multiple_bases) {
  int a1, a2, b1, b2, c1, c2;
  ASSERT_SSCANF_EQUAL3("123 0777 0xFF", "%i %i %i", &a1, &b1, &c1, &a2, &b2,
                       &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t095_i_multiple_decimal) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("123 456 789 101", "%i %i %i %i", &a1, &b1, &c1, &d1,
                       &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t096_i_multiple_octal) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("012 077 034 010", "%i %i %i %i", &a1, &b1, &c1, &d1,
                       &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t097_i_multiple_hex) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("0x1a 0XFF 0xabcd 0X12", "%i %i %i %i", &a1, &b1, &c1,
                       &d1, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t098_i_mixed_formats) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("123 0x1f 077 -100", "%i %i %i %i", &a1, &b1, &c1, &d1,
                       &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t099_i_multiple_spaces) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("   100   -0XABC   012   12345   ", "%i %i %i %i", &a1,
                       &b1, &c1, &d1, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t100_i_multiple_invalid) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("abc def ghi jkl", "%i %i %i %i", &a1, &b1, &c1, &d1,
                       &a2, &b2, &c2, &d2);
}
END_TEST

START_TEST(t101_i_partial_invalid) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("123 abc 0x10 789", "%i %i %i %i", &a1, &b1, &c1, &d1,
                       &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t102_i_multiple_overflow) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("2147483648 9999999999 -2147483649 123", "%i %i %i %i",
                       &a1, &b1, &c1, &d1, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t103_i_skip_multiple) {
  int a1, d1, a2, d2;
  ASSERT_SSCANF_EQUAL4("0x1a 123 077 999", "%*i %i %*i %i", &a1, &d1, &a2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t104_i_multiple_negative) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("-123 -0x1a -077 -456", "%i %i %i %i", &a1, &b1, &c1,
                       &d1, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t105_i_multiple_zero) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("0 -0 0x0 -0x0", "%i %i %i %i", &a1, &b1, &c1, &d1, &a2,
                       &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t106_i_multiple_whitespace) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8(" \t\n\r0x1\t077\v  123\f0XAB ", "%i %i %i %i", &a1, &b1,
                       &c1, &d1, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(t107_i_multiple_empty) {
  int a1, b1, c1, d1, a2, b2, c2, d2;
  ASSERT_SSCANF_EQUAL8("", "%i %i %i %i", &a1, &b1, &c1, &d1, &a2, &b2, &c2,
                       &d2);
}
END_TEST

START_TEST(t108_i_int_max) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("2147483647", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t109_i_int_min) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("-2147483648", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t110_i_overflow_positive) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("2147483648", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t111_i_overflow_negative) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("-2147483649", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t112_i_huge_positive) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("9999999999999999999999999999999999999999", "%i", &num1,
                      &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t113_i_huge_negative) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("-9999999999999999999999999999999999999999", "%i", &num1,
                      &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t114_i_hex_max) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0x7FFFFFFF", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t115_i_hex_overflow) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0x80000000", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t116_i_octal_max) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("037777777777", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t117_i_octal_overflow) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("040000000000", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t118_i_invalid_hex) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("0xG", "%i", &num1, &num2);
}
END_TEST

START_TEST(t119_i_huge_with_zero) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("99999999999999999999999999999999999999990", "%i", &num1,
                      &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t120_i_huge_negative_with_zero) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("-99999999999999999999999999999999999999990", "%i", &num1,
                      &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t121_i_long_octal) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("017777777777", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t122_i_only_sign) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("+", "%i", &num1, &num2);
}
END_TEST

START_TEST(t123_i_null_string) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("\0", "%i", &num1, &num2);
}
END_TEST

START_TEST(t124_i_spaces_before_hex) {
  int num1, num2;
  ASSERT_SSCANF_EQUAL("  -0XABC", "%i", &num1, &num2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(t125_i_multiple_hex) {
  int a1, b1, c1, a2, b2, c2;
  ASSERT_SSCANF_EQUAL3("0x1a 0XFF -0x1", "%i %i %i", &a1, &b1, &c1, &a2, &b2,
                       &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t126_i_skip_hex) {
  int a1, c1, a2, c2;
  ASSERT_SSCANF_EQUAL4("0x1a 0XFF -0x1", "%*i %i %i", &a1, &c1, &a2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t127_i_width_hex) {
  int a1, b1, a2, b2;
  ASSERT_SSCANF_EQUAL4("0x1a0xFF", "%2i %2i", &a1, &b1, &a2, &b2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(t128_i_hex_max) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("0x7FFFFFFF", "%i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t129_i_hex_overflow) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("0x80000000", "%i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t130_i_negative_hex_overflow) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("-0x80000001", "%i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t131_i_mixed_hex_decimal) {
  int a1, b1, c1, a2, b2, c2;
  ASSERT_SSCANF_EQUAL3("0x10 123 0xabc", "%i %i %i", &a1, &b1, &c1, &a2, &b2,
                       &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t132_i_width_long_hex) {
  int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
  ASSERT_SSCANF_EQUAL4("0x1abcdef", "%5i %i", &a1, &b1, &a2, &b2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(t133_i_width_negative_hex) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("-0x1abcdef", "%6i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t134_i_very_long_hex) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("0x123456789ABCDEF", "%i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t135_i_spaces_between_hex) {
  int a1, b1, c1, a2, b2, c2;
  ASSERT_SSCANF_EQUAL3("   0x1a   0XFF   -0x1   ", "%i %i %i", &a1, &b1, &c1,
                       &a2, &b2, &c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(t136_i_width_partial_hex) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("0x1234ABCD", "%7i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t137_i_invalid_hex) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("0xG1A", "%i", &a1, &a2);
}
END_TEST

START_TEST(t138_i_skip_multiple_hex) {
  int a1, a2;
  ASSERT_SSCANF_EQUAL("0x1a 0XFF", "%*i %i", &a1, &a2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(t139_i_hex_zero) {
  int a1, b1, a2, b2;
  ASSERT_SSCANF_EQUAL4("0x0 -0x0", "%i %i", &a1, &b1, &a2, &b2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(t141_e_basic) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("1.23e5", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t142_e_negative) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("-1.23e5", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t143_e_positive_sign) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("+1.23e5", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t144_e_width_4) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("+1.23e5", "%4le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t145_e_width_3) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("+1.23e5", "%3le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t146_E_basic) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("1.2E+05", "%lE", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t147_e_width_limit) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("123456789e10", "%5le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t148_e_skip) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("1.23e4 5.67E8", "%*e %lE", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t149_e_multiple_zeros) {
  double f1, f2, f3, f4, f5, f6;
  ASSERT_SSCANF_EQUAL3("0e0 0E0 0", "%le %lE %le", &f1, &f2, &f3, &f4, &f5,
                       &f6);
  ck_assert_double_eq_tol(f1, f4, 1e-6);
  ck_assert_double_eq_tol(f2, f5, 1e-6);
  ck_assert_double_eq_tol(f3, f6, 1e-6);
}
END_TEST

START_TEST(t150_e_no_fraction) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("123e5", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t151_e_negative_exp) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("-123456.789e-10", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t152_e_spaces) {
  double f1, f2, f3, f4;
  ASSERT_SSCANF_EQUAL4("   1.23e4   5.67E8   ", "%le %lE", &f1, &f2, &f3, &f4);
  ck_assert_double_eq_tol(f1, f3, 1e-6);
  ck_assert_double_eq_tol(f2, f4, 1e-6);
}
END_TEST

START_TEST(t153_e_empty) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("", "%le", &f1, &f2);
}
END_TEST

START_TEST(t154_e_only_spaces) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("     ", "%le", &f1, &f2);
}
END_TEST

START_TEST(t155_e_invalid) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("abc", "%le", &f1, &f2);
}
END_TEST

START_TEST(t156_e_partial_invalid) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("123eX", "%le", &f1, &f2);
}
END_TEST

START_TEST(t157_e_large_number) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("1e308", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t158_e_large_negative) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("-1e308", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t159_e_no_exp) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("123.45", "%le", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t161_e_mixed_skip) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("0x1a 1.2e3 abc", "%*e %le %*e", &f1, &f2);
  ck_assert_double_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(t162_e_double_dot) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL("1..2e3", "%le", &f1, &f2);
}
END_TEST

START_TEST(t163_f_basic) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123.45", "%lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t164_g_exponential) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123.45e6", "%lg", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t165_f_width) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123456789.123", "%5lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t166_g_skip) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123.45 678.90", "%*g %lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t167_mixed_format) {
  double d1, d2, d3, d4;
  ASSERT_SSCANF_EQUAL4("123.45 678.90 901.23", "%lf %*F %lg", &d1, &d2, &d3,
                       &d4);
  ck_assert_double_eq_tol(d1, d3, 1e-6);
  ck_assert_double_eq_tol(d2, d4, 1e-6);
}
END_TEST

START_TEST(t168_f_negative) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("-123.45", "%lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t169_multiple_zeros) {
  double d1, d2, d3, d4, d5, d6;
  ASSERT_SSCANF_EQUAL3("0.0 0.0 0.0", "%lf %lF %lg", &d1, &d2, &d3, &d4, &d5,
                       &d6);
  ck_assert_double_eq_tol(d1, d4, 1e-6);
  ck_assert_double_eq_tol(d2, d5, 1e-6);
  ck_assert_double_eq_tol(d3, d6, 1e-6);
}
END_TEST

START_TEST(t170_f_no_fraction) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123", "%lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t171_f_width_negative) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("-123456.789", "%10lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t172_g_G_spaces) {
  double d1, d2, d3, d4;
  ASSERT_SSCANF_EQUAL4("   123.45   -901.23E5   ", "%lg %lG", &d1, &d2, &d3,
                       &d4);
  ck_assert_double_eq_tol(d1, d3, 1e-6);
  ck_assert_double_eq_tol(d2, d4, 1e-6);
}
END_TEST

START_TEST(t173_f_empty) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("", "%lf", &d1, &d2);
}
END_TEST

START_TEST(t174_G_only_spaces) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("     ", "%lG", &d1, &d2);
}
END_TEST

START_TEST(t175_f_invalid) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("abc", "%lf", &d1, &d2);
}
END_TEST

START_TEST(t176_f_partial_invalid) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123.45.67", "%lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t177_g_large) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("1e308", "%lg", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t178_G_large_negative) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("-1e308", "%lG", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t179_f_no_integer) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL(".123", "%lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t180_f_skip_width) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("1.234 5.678", "%*f %lf", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t181_f_mixed_skip) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("0x1a 1.2 .e5 abc", "%*f %lf %*f", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t182_f_double_dot) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("1..2", "%lf", &d1, &d2);
}
END_TEST

START_TEST(t183_F_with_exp) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123e5", "%lF", &d1, &d2);
}
END_TEST

START_TEST(t184_g_precision) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("123.987654321", "%lg", &d1, &d2);
  ck_assert_double_eq_tol(d1, d2, 1e-6);
}
END_TEST

START_TEST(t186_g_nan) {
  double d1, d2;
  ASSERT_SSCANF_EQUAL("nan", "%lg", &d1, &d2);
}
END_TEST

START_TEST(t187_o_short_basic) {
  unsigned short us1, us2;
  ASSERT_SSCANF_EQUAL("177", "%ho", &us1, &us2);
  ck_assert_uint_eq(us1, us2);
}
END_TEST

START_TEST(t188_o_short_overflow) {
  unsigned short us1, us2;
  ASSERT_SSCANF_EQUAL("40000", "%ho", &us1, &us2);
  ck_assert_uint_eq(us1, us2);
}
END_TEST

START_TEST(t189_o_basic) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("123", "%o", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t190_o_zero) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("0", "%o", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t191_o_negative) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("-12", "%o", &ui1, &ui2);
}
END_TEST

START_TEST(t192_o_long_max) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("17777777777", "%lo", &ul1, &ul2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t193_o_long_overflow) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("7777777777777777777777", "%lo", &ul1, &ul2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t194_o_width) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("123456", "%3o", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t195_o_skip) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("123 456", "%*o %o", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t196_o_mixed_lengths) {
  unsigned short us1, us2;
  unsigned int ui1, ui2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL3("177 123 17777777777", "%ho %o %lo", &us1, &ui1, &ul1,
                       &us2, &ui2, &ul2);
  ck_assert_uint_eq(us1, us2);
  ck_assert_uint_eq(ui1, ui2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t197_o_spaces_before) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("   123", "%o", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t198_o_empty) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("", "%o", &ui1, &ui2);
}
END_TEST

START_TEST(t199_o_invalid_input) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("abc", "%o", &ui1, &ui2);
}
END_TEST

START_TEST(t200_o_invalid_digit) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("09", "%o", &ui1, &ui2);
}
END_TEST

START_TEST(t201_o_skip_width) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("123456", "%*2o %o", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t202_o_mixed_skip) {
  unsigned int ui1, ui2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL4("12 34 56", "%o %*o %lo", &ui1, &ul1, &ui2, &ul2);
  ck_assert_uint_eq(ui1, ui2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t203_o_whitespace_mix) {
  unsigned int ui1, ui2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL4(" \t\n\r012\v\f034", "%o %lo", &ui1, &ul1, &ui2, &ul2);
  ck_assert_uint_eq(ui1, ui2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t204_o_zero_negative) {
  unsigned int ui1, ui2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL4("0 -0", "%o %lo", &ui1, &ul1, &ui2, &ul2);
  ck_assert_uint_eq(ui1, ui2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t205_x_basic) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("1a", "%x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t206_X_uppercase) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("ABC", "%X", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t207_x_skip) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("1a 2b", "%*x %x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t208_hx_basic) {
  unsigned short us1, us2;
  ASSERT_SSCANF_EQUAL("12ab", "%hx", &us1, &us2);
  ck_assert_uint_eq(us1, us2);
}
END_TEST

START_TEST(t209_hx_overflow) {
  unsigned short us1, us2;
  ASSERT_SSCANF_EQUAL("123456", "%hx", &us1, &us2);
  ck_assert_uint_eq(us1, us2);
}
END_TEST

START_TEST(t210_lx_basic) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("123abcde", "%lx", &ul1, &ul2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t211_x_negative) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("-1a", "%x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t212_x_skip_width) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("123456", "%*3x %x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t213_hX_uppercase) {
  unsigned short us1, us2;
  ASSERT_SSCANF_EQUAL("0XABCD", "%hX", &us1, &us2);
  ck_assert_uint_eq(us1, us2);
}
END_TEST

START_TEST(t214_lX_uppercase) {
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL("0X12345678", "%lX", &ul1, &ul2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t215_x_mixed_case) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("1aBc2D", "%x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t216_x_zero) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("0", "%x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t217_x_spaces) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("   1a", "%x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t218_x_invalid) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("xyz", "%x", &ui1, &ui2);
}
END_TEST

START_TEST(t219_x_partial) {
  unsigned int ui1, ui2;
  ASSERT_SSCANF_EQUAL("1g2", "%x", &ui1, &ui2);
  ck_assert_uint_eq(ui1, ui2);
}
END_TEST

START_TEST(t220_x_multiple) {
  unsigned int ui1, ui2;
  unsigned long ul1, ul2;
  ASSERT_SSCANF_EQUAL4("1a 2b 3c", "%x %lx", &ui1, &ul1, &ui2, &ul2);
  ck_assert_uint_eq(ui1, ui2);
  ck_assert_uint_eq(ul1, ul2);
}
END_TEST

START_TEST(t221_ptr_basic) {
  void *ptr1, *ptr2;
  ASSERT_SSCANF_EQUAL("0x12345678", "%p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t223_ptr_spaces) {
  void *ptr1, *ptr2;
  ASSERT_SSCANF_EQUAL("   0xABCD   ", "%p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t224_ptr_invalid) {
  void *ptr1 = NULL, *ptr2 = NULL;
  ASSERT_SSCANF_EQUAL("invalid", "%p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t225_ptr_multiple) {
  void *ptr1, *ptr2, *ptr3, *ptr4;
  ASSERT_SSCANF_EQUAL4("0x123 0xABC", "%p %p", &ptr1, &ptr2, &ptr3, &ptr4);
  ck_assert_ptr_eq(ptr1, ptr3);
  ck_assert_ptr_eq(ptr2, ptr4);
}
END_TEST

START_TEST(t226_ptr_width) {
  void *ptr1, *ptr2;
  ASSERT_SSCANF_EQUAL("0x12345678", "%10p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t227_ptr_zero) {
  void *ptr1, *ptr2;
  ASSERT_SSCANF_EQUAL("0x0", "%p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t228_ptr_skip) {
  void *ptr1, *ptr2;
  ASSERT_SSCANF_EQUAL("0x123 0xABC", "%*p %p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t229_ptr_mixed) {
  void *ptr1, *ptr2;
  int i1, i2;
  ASSERT_SSCANF_EQUAL4("0xABC 123", "%p %d", &ptr1, &i1, &ptr2, &i2);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(t230_ptr_hex_variants) {
  void *ptr1, *ptr2;
  ASSERT_SSCANF_EQUAL("0XABCD", "%p", &ptr1, &ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(t231_s_skip_width) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("abcdefg hij", "%*5s %s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t232_s_mixed_skip) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("one two three", "%*s %s %*s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t233_s_skip_read) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("hello world", "%*s %s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t234_s_width_exact) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("apple", "%5s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t235_s_width_partial) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("abcdefg", "%3s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t236_s_multiple_spaces) {
  char buf1[100], buf2[100], buf3[100], buf4[100];
  ASSERT_SSCANF_EQUAL4("   123   hello", "%s %s", buf1, buf2, buf3, buf4);
  ck_assert_str_eq(buf1, buf3);
  ck_assert_str_eq(buf2, buf4);
}
END_TEST

START_TEST(t237_s_special_chars) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("hello\tworld", "%5s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t238_s_newlines) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("hello\n\n\nworld", "%s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t239_s_empty) {
  char buf1[100], buf2[100];
  buf1[0] = buf2[0] = 'X';
  ASSERT_SSCANF_EQUAL("", "%s", buf1, buf2);
}
END_TEST

START_TEST(t240_s_only_spaces) {
  char buf1[100], buf2[100];
  buf1[0] = buf2[0] = 'X';
  ASSERT_SSCANF_EQUAL("     ", "%s", buf1, buf2);
}
END_TEST

START_TEST(t242_s_long_string) {
  char buf1[100], buf2[100];
  ASSERT_SSCANF_EQUAL("abcdefghijklmnopqrstuvwxyz", "%10s", buf1, buf2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(t243_n_middle) {
  int n1 = 0, n2 = 0;
  int val1 = 0, val3 = 0;
  ASSERT_SSCANF_EQUAL3("123%n456", "%d%n%d", &val1, &n1, &val3, &val3, &n2,
                       &val3);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(t244_n_end) {
  int n1 = 0, n2 = 0;
  int val1 = 0, val2 = 0;
  ASSERT_SSCANF_EQUAL4("123", "%d%n", &val1, &n1, &val2, &n2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(t246_percent_match) {
  int val1 = 0, val2 = 0;
  ASSERT_SSCANF_EQUAL2("123", "%%%d", &val1, &val2);
  ck_assert_int_eq(val1, val2);
}
END_TEST

START_TEST(t247_percent_mismatch) {
  int val1 = 0, val2 = 0;
  ASSERT_SSCANF_EQUAL2("x123", "%%%d", &val1, &val2);
  ck_assert_int_eq(val1, val2);
}
END_TEST

START_TEST(t248_percent_multiple) {
  int val1 = 0, val2 = 0;
  ASSERT_SSCANF_EQUAL2("%123", "%%%d", &val1, &val2);
  ck_assert_int_eq(val1, val2);
}
END_TEST

START_TEST(t253_skip_char) { ASSERT_SSCANF_EQUAL_NOARG("a", "%*c"); }
END_TEST

START_TEST(t261_negative_octal) {
  unsigned short s1, s2;
  ASSERT_SSCANF_EQUAL2("777", "%ho", &s1, &s2);
}
END_TEST

START_TEST(t250_regular_char_mismatch) {
  char str[] = "a";
  ASSERT_SSCANF_EQUAL2("b", "%c", str, str);
}
END_TEST

START_TEST(t251_n_specifier) {
  int val1 = 0, val2 = 0;
  int n1 = 0, n2 = 0;
  ASSERT_SSCANF_EQUAL4("123", "%d%n", &val1, &n1, &val2, &n2);
  ck_assert_int_eq(val1, val2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(t252_symbol_test) {
  char c1, c2;
  ASSERT_SSCANF_EQUAL4("aB", "%c%c", &c1, &c2, &c1, &c2);
}
END_TEST

START_TEST(t254_decimal_overflow) {
  int n1, n2;
  ASSERT_SSCANF_EQUAL2("9999999999999999999", "%d", &n1, &n2);
}
END_TEST

START_TEST(t255_unsigned_width) {
  unsigned u1, u2;
  ASSERT_SSCANF_EQUAL2("12345", "%3u", &u1, &u2);
}
END_TEST

START_TEST(t256_short_int) {
  short s1, s2;
  ASSERT_SSCANF_EQUAL2("32767", "%hi", &s1, &s2);
}
END_TEST

START_TEST(t257_long_int) {
  long l1, l2;
  ASSERT_SSCANF_EQUAL2("2147483647", "%ld", &l1, &l2);
}
END_TEST

START_TEST(t258_float_infinity) {
  double f2;
  char str[] = "infinity";
  int ret2 = s21_sscanf(str, "%f", &f2);
  ck_assert_int_eq(1, ret2);
  ck_assert_float_eq(f2, INFINITY);
}
END_TEST

START_TEST(t259_float_nan) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL2("NAN", "%lf", &f1, &f2);
}
END_TEST

START_TEST(t260_hex_float) {
  double f1, f2;
  ASSERT_SSCANF_EQUAL2("10.5", "%lf", &f1, &f2);
}
END_TEST

START_TEST(t265_unsigned_overflow_width) {
  unsigned u1, u2;

  ASSERT_SSCANF_EQUAL2("18446744073709551616", "%5u", &u1, &u2);
}
END_TEST

START_TEST(t266_unsigned_overflow_no_width) {
  unsigned u1, u2;

  ASSERT_SSCANF_EQUAL2("18446744073709551616", "%u", &u1, &u2);
}
END_TEST

START_TEST(t267_unsigned_width_sign) {
  unsigned u1, u2;
  ASSERT_SSCANF_EQUAL2("-12345", "%4u", &u1, &u2);
}
END_TEST

START_TEST(t268_unsigned_max) {
  unsigned long ul1, ul2;

  ASSERT_SSCANF_EQUAL2("18446744073709551615", "%lu", &ul1, &ul2);
}
END_TEST

START_TEST(t269_unsigned_width_continue) {
  unsigned u1, u2;
  ASSERT_SSCANF_EQUAL2("123456", "%3u", &u1, &u2);
}
END_TEST

START_TEST(t270_unsigned_empty) {
  unsigned u1, u2;
  ASSERT_SSCANF_EQUAL2("", "%u", &u1, &u2);
}
END_TEST

START_TEST(t271_unsigned_invalid) {
  unsigned u1, u2;
  ASSERT_SSCANF_EQUAL2("abc", "%u", &u1, &u2);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc = tcase_create("all");

  tcase_add_test(tc, t001_char);
  tcase_add_test(tc, t002_decimal);
  tcase_add_test(tc, t003_float);
  tcase_add_test(tc, t004_string);
  tcase_add_test(tc, t005_exp_lower);
  tcase_add_test(tc, t006_exp_upper);
  tcase_add_test(tc, t007_g_auto);
  tcase_add_test(tc, t008_G_auto);
  tcase_add_test(tc, t009_hex_lower);
  tcase_add_test(tc, t010_hex_upper);
  tcase_add_test(tc, t011_octal);
  tcase_add_test(tc, t012_pointer);
  tcase_add_test(tc, t013_width_number);
  tcase_add_test(tc, t014_width_asterisk);
  tcase_add_test(tc, t017_short);
  tcase_add_test(tc, t018_long);
  tcase_add_test(tc, t019_long_double);
  tcase_add_test(tc, t020_combined);
  tcase_add_test(tc, t021_empty);
  tcase_add_test(tc, t022_whitespace);
  tcase_add_test(tc, t023_max_values);
  tcase_add_test(tc, t024_min_values);
  tcase_add_test(tc, t026_combined_hex_dec);
  tcase_add_test(tc, t027_n_basic);
  tcase_add_test(tc, t030_empty_format);
  tcase_add_test(tc, t031_only_spaces_input);
  tcase_add_test(tc, t032_no_match);
  tcase_add_test(tc, t033_overflow);
  tcase_add_test(tc, t034_multiple_spaces);
  tcase_add_test(tc, t035_mixed_hex);
  tcase_add_test(tc, t036_zero_values);
  tcase_add_test(tc, t037_negative_zero);
  tcase_add_test(tc, t038_mixed_separators);
  tcase_add_test(tc, t039_consecutive_chars);

  tcase_add_test(tc, t045_int_width_spaces);
  tcase_add_test(tc, t046_int_negative_width3);
  tcase_add_test(tc, t047_int_positive_width2);
  tcase_add_test(tc, t048_int_negative_width2);
  tcase_add_test(tc, t049_int_empty_str);
  tcase_add_test(tc, t050_int_regular);
  tcase_add_test(tc, t051_int_negative);
  tcase_add_test(tc, t052_int_positive_sign);
  tcase_add_test(tc, t053_int_width_3);
  tcase_add_test(tc, t054_int_width_2);
  tcase_add_test(tc, t055_int_skip);
  tcase_add_test(tc, t056_int_skip_width);
  tcase_add_test(tc, t057_int_partial_invalid);
  tcase_add_test(tc, t058_int_mixed_input);
  tcase_add_test(tc, t059_int_overflow_positive);
  tcase_add_test(tc, t060_short_int_max);
  tcase_add_test(tc, t061_short_int_min);
  tcase_add_test(tc, t062_short_int_overflow_positive);
  tcase_add_test(tc, t063_short_int_overflow_negative);
  tcase_add_test(tc, t064_unsigned_short_max);
  tcase_add_test(tc, t065_unsigned_short_negative);
  tcase_add_test(tc, t066_unsigned_short_overflow);
  tcase_add_test(tc, t067_long_int_max);
  tcase_add_test(tc, t068_long_int_min);
  tcase_add_test(tc, t069_long_int_overflow_positive);
  tcase_add_test(tc, t070_long_int_overflow_negative);
  tcase_add_test(tc, t071_unsigned_long_max);
  tcase_add_test(tc, t072_unsigned_long_negative);
  tcase_add_test(tc, t073_unsigned_long_overflow);
  tcase_add_test(tc, t074_mixed_short_and_long);
  tcase_add_test(tc, t075_mixed_long_overflow);
  tcase_add_test(tc, t076_unsigned_long_empty_input);
  tcase_add_test(tc, t077_unsigned_long_empty_string);

  tcase_add_test(tc, t080_i_decimal);
  tcase_add_test(tc, t081_i_octal);
  tcase_add_test(tc, t082_i_hex_lower);
  tcase_add_test(tc, t083_i_hex_upper);
  tcase_add_test(tc, t084_i_negative_hex);
  tcase_add_test(tc, t085_i_invalid_input);
  tcase_add_test(tc, t086_i_only_spaces);
  tcase_add_test(tc, t087_i_empty_string);
  tcase_add_test(tc, t088_i_overflow_positive);
  tcase_add_test(tc, t089_i_overflow_negative);
  tcase_add_test(tc, t090_i_mixed_success_failure);
  tcase_add_test(tc, t091_i_width);
  tcase_add_test(tc, t092_i_skip_asterisk);
  tcase_add_test(tc, t093_i_zero_values);
  tcase_add_test(tc, t094_i_multiple_bases);
  tcase_add_test(tc, t095_i_multiple_decimal);
  tcase_add_test(tc, t096_i_multiple_octal);
  tcase_add_test(tc, t097_i_multiple_hex);
  tcase_add_test(tc, t098_i_mixed_formats);
  tcase_add_test(tc, t099_i_multiple_spaces);
  tcase_add_test(tc, t100_i_multiple_invalid);
  tcase_add_test(tc, t101_i_partial_invalid);
  tcase_add_test(tc, t102_i_multiple_overflow);
  tcase_add_test(tc, t103_i_skip_multiple);
  tcase_add_test(tc, t104_i_multiple_negative);
  tcase_add_test(tc, t105_i_multiple_zero);
  tcase_add_test(tc, t106_i_multiple_whitespace);
  tcase_add_test(tc, t107_i_multiple_empty);
  tcase_add_test(tc, t108_i_int_max);
  tcase_add_test(tc, t109_i_int_min);
  tcase_add_test(tc, t110_i_overflow_positive);
  tcase_add_test(tc, t111_i_overflow_negative);
  tcase_add_test(tc, t112_i_huge_positive);
  tcase_add_test(tc, t113_i_huge_negative);
  tcase_add_test(tc, t114_i_hex_max);
  tcase_add_test(tc, t115_i_hex_overflow);
  tcase_add_test(tc, t116_i_octal_max);
  tcase_add_test(tc, t117_i_octal_overflow);
  tcase_add_test(tc, t118_i_invalid_hex);
  tcase_add_test(tc, t119_i_huge_with_zero);
  tcase_add_test(tc, t120_i_huge_negative_with_zero);
  tcase_add_test(tc, t121_i_long_octal);
  tcase_add_test(tc, t122_i_only_sign);
  tcase_add_test(tc, t123_i_null_string);
  tcase_add_test(tc, t124_i_spaces_before_hex);
  tcase_add_test(tc, t125_i_multiple_hex);
  tcase_add_test(tc, t126_i_skip_hex);
  tcase_add_test(tc, t127_i_width_hex);
  tcase_add_test(tc, t128_i_hex_max);
  tcase_add_test(tc, t129_i_hex_overflow);
  tcase_add_test(tc, t130_i_negative_hex_overflow);
  tcase_add_test(tc, t131_i_mixed_hex_decimal);
  tcase_add_test(tc, t132_i_width_long_hex);
  tcase_add_test(tc, t133_i_width_negative_hex);
  tcase_add_test(tc, t134_i_very_long_hex);
  tcase_add_test(tc, t135_i_spaces_between_hex);
  tcase_add_test(tc, t136_i_width_partial_hex);
  tcase_add_test(tc, t137_i_invalid_hex);
  tcase_add_test(tc, t138_i_skip_multiple_hex);
  tcase_add_test(tc, t139_i_hex_zero);
  tcase_add_test(tc, t141_e_basic);
  tcase_add_test(tc, t142_e_negative);
  tcase_add_test(tc, t143_e_positive_sign);
  tcase_add_test(tc, t144_e_width_4);
  tcase_add_test(tc, t145_e_width_3);
  tcase_add_test(tc, t146_E_basic);
  tcase_add_test(tc, t147_e_width_limit);
  tcase_add_test(tc, t148_e_skip);
  tcase_add_test(tc, t149_e_multiple_zeros);
  tcase_add_test(tc, t150_e_no_fraction);
  tcase_add_test(tc, t151_e_negative_exp);
  tcase_add_test(tc, t152_e_spaces);
  tcase_add_test(tc, t153_e_empty);
  tcase_add_test(tc, t154_e_only_spaces);
  tcase_add_test(tc, t155_e_invalid);
  tcase_add_test(tc, t156_e_partial_invalid);
  tcase_add_test(tc, t157_e_large_number);
  tcase_add_test(tc, t158_e_large_negative);
  tcase_add_test(tc, t159_e_no_exp);
  tcase_add_test(tc, t161_e_mixed_skip);
  tcase_add_test(tc, t162_e_double_dot);
  tcase_add_test(tc, t163_f_basic);
  tcase_add_test(tc, t164_g_exponential);
  tcase_add_test(tc, t165_f_width);
  tcase_add_test(tc, t166_g_skip);
  tcase_add_test(tc, t167_mixed_format);
  tcase_add_test(tc, t168_f_negative);
  tcase_add_test(tc, t169_multiple_zeros);
  tcase_add_test(tc, t170_f_no_fraction);
  tcase_add_test(tc, t171_f_width_negative);
  tcase_add_test(tc, t172_g_G_spaces);
  tcase_add_test(tc, t173_f_empty);
  tcase_add_test(tc, t174_G_only_spaces);
  tcase_add_test(tc, t175_f_invalid);
  tcase_add_test(tc, t176_f_partial_invalid);
  tcase_add_test(tc, t177_g_large);
  tcase_add_test(tc, t178_G_large_negative);
  tcase_add_test(tc, t179_f_no_integer);
  tcase_add_test(tc, t180_f_skip_width);
  tcase_add_test(tc, t181_f_mixed_skip);
  tcase_add_test(tc, t182_f_double_dot);
  tcase_add_test(tc, t183_F_with_exp);
  tcase_add_test(tc, t184_g_precision);
  tcase_add_test(tc, t186_g_nan);
  tcase_add_test(tc, t187_o_short_basic);
  tcase_add_test(tc, t188_o_short_overflow);
  tcase_add_test(tc, t189_o_basic);
  tcase_add_test(tc, t190_o_zero);
  tcase_add_test(tc, t191_o_negative);
  tcase_add_test(tc, t192_o_long_max);
  tcase_add_test(tc, t193_o_long_overflow);
  tcase_add_test(tc, t194_o_width);
  tcase_add_test(tc, t195_o_skip);
  tcase_add_test(tc, t196_o_mixed_lengths);
  tcase_add_test(tc, t197_o_spaces_before);
  tcase_add_test(tc, t198_o_empty);
  tcase_add_test(tc, t199_o_invalid_input);
  tcase_add_test(tc, t200_o_invalid_digit);
  tcase_add_test(tc, t201_o_skip_width);
  tcase_add_test(tc, t202_o_mixed_skip);
  tcase_add_test(tc, t203_o_whitespace_mix);
  tcase_add_test(tc, t204_o_zero_negative);
  tcase_add_test(tc, t205_x_basic);
  tcase_add_test(tc, t206_X_uppercase);
  tcase_add_test(tc, t207_x_skip);
  tcase_add_test(tc, t208_hx_basic);
  tcase_add_test(tc, t209_hx_overflow);
  tcase_add_test(tc, t210_lx_basic);
  tcase_add_test(tc, t211_x_negative);
  tcase_add_test(tc, t212_x_skip_width);
  tcase_add_test(tc, t213_hX_uppercase);
  tcase_add_test(tc, t214_lX_uppercase);
  tcase_add_test(tc, t215_x_mixed_case);
  tcase_add_test(tc, t216_x_zero);
  tcase_add_test(tc, t217_x_spaces);
  tcase_add_test(tc, t218_x_invalid);
  tcase_add_test(tc, t219_x_partial);
  tcase_add_test(tc, t220_x_multiple);
  tcase_add_test(tc, t221_ptr_basic);
  tcase_add_test(tc, t223_ptr_spaces);
  tcase_add_test(tc, t224_ptr_invalid);
  tcase_add_test(tc, t225_ptr_multiple);
  tcase_add_test(tc, t226_ptr_width);
  tcase_add_test(tc, t227_ptr_zero);
  tcase_add_test(tc, t228_ptr_skip);
  tcase_add_test(tc, t229_ptr_mixed);
  tcase_add_test(tc, t230_ptr_hex_variants);
  tcase_add_test(tc, t231_s_skip_width);
  tcase_add_test(tc, t232_s_mixed_skip);
  tcase_add_test(tc, t233_s_skip_read);
  tcase_add_test(tc, t234_s_width_exact);
  tcase_add_test(tc, t235_s_width_partial);
  tcase_add_test(tc, t236_s_multiple_spaces);
  tcase_add_test(tc, t237_s_special_chars);
  tcase_add_test(tc, t238_s_newlines);
  tcase_add_test(tc, t239_s_empty);
  tcase_add_test(tc, t240_s_only_spaces);
  tcase_add_test(tc, t242_s_long_string);
  tcase_add_test(tc, t243_n_middle);
  tcase_add_test(tc, t244_n_end);
  tcase_add_test(tc, t246_percent_match);
  tcase_add_test(tc, t247_percent_mismatch);
  tcase_add_test(tc, t248_percent_multiple);
  tcase_add_test(tc, t250_regular_char_mismatch);
  tcase_add_test(tc, t251_n_specifier);
  tcase_add_test(tc, t252_symbol_test);
  tcase_add_test(tc, t253_skip_char);
  tcase_add_test(tc, t254_decimal_overflow);
  tcase_add_test(tc, t255_unsigned_width);
  tcase_add_test(tc, t256_short_int);
  tcase_add_test(tc, t257_long_int);
  tcase_add_test(tc, t258_float_infinity);
  tcase_add_test(tc, t259_float_nan);
  tcase_add_test(tc, t260_hex_float);
  tcase_add_test(tc, t261_negative_octal);
  tcase_add_test(tc, t265_unsigned_overflow_width);
  tcase_add_test(tc, t266_unsigned_overflow_no_width);
  tcase_add_test(tc, t267_unsigned_width_sign);
  tcase_add_test(tc, t268_unsigned_max);
  tcase_add_test(tc, t269_unsigned_width_continue);
  tcase_add_test(tc, t270_unsigned_empty);
  tcase_add_test(tc, t271_unsigned_invalid);
  suite_add_tcase(s, tc);
  return s;
}