#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main_test_unit.h"
#include "s21_string.h"

START_TEST(test_memchr_various) {
  char str1[] = "abc\0def";
  ck_assert_ptr_eq(memchr(str1, '\0', 7), s21_memchr(str1, '\0', 7));
  ck_assert_ptr_eq(memchr(str1, 'a', 1), s21_memchr(str1, 'a', 1));
  ck_assert_ptr_eq(memchr(str1, 'd', 7), s21_memchr(str1, 'd', 7));
  ck_assert_ptr_eq(memchr(str1, 'z', 7), s21_memchr(str1, 'z', 7));
}
END_TEST

START_TEST(test_s21_memchr_basic) {
  const char *str = "Hello, school!";
  int c = 'o';
  size_t len = strlen(str);
  void *result = s21_memchr(str, c, len);
  void *expected = memchr(str, c, len);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_memchr_not_found) {
  const char *str = "Hello, school!";
  int c = 'z';
  size_t len = strlen(str);
  void *result = s21_memchr(str, c, len);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_memchr_zero_length) {
  const char *str = "Hello, school!";
  int c = 'H';
  void *result = s21_memchr(str, c, 0);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_memchr_partial) {
  const char *str = "Hello, school!";
  int c = '!';
  void *result = s21_memchr(str, c, 5);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_memchr_binary_found) {
  unsigned char data[] = {0x00, 0x01, 0x02, 0x03, 0xFF};
  unsigned char c = 0xFF;
  void *result = s21_memchr(data, c, sizeof(data));
  void *expected = memchr(data, c, sizeof(data));
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_memchr_binary_not_found) {
  unsigned char data[] = {0x00, 0x01, 0x02, 0x03, 0xFF};
  unsigned char c = 0x03;
  void *result = s21_memchr(data, c, 2);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_memcmp_various) {
  char a[] = "abcde";
  char b[] = "abcdf";
  char c[] = "abcde";
  ck_assert_int_eq(memcmp(a, b, 4), s21_memcmp(a, b, 4));
  ck_assert_int_eq(memcmp(a, b, 5), s21_memcmp(a, b, 5));
  ck_assert_int_eq(memcmp(a, c, 5), s21_memcmp(a, c, 5));
  ck_assert_int_eq(memcmp("", "", 1), s21_memcmp("", "", 1));
}
END_TEST

START_TEST(test_s21_memcmp_equal) {
  const char *str1 = "Hello, school!";
  const char *str2 = "Hello, school!";
  size_t n = strlen(str1);
  ck_assert_int_eq(s21_memcmp(str1, str2, n), 0);
}
END_TEST

START_TEST(test_s21_memcmp_not_equal) {
  const char *str1 = "Hello, school!";
  const char *str2 = "Hello, School!";
  size_t n = strlen(str1);
  int result = s21_memcmp(str1, str2, n);
  ck_assert(result != 0);
}
END_TEST

START_TEST(test_s21_memcmp_figure_less) {
  const char *str1 = "123456789";
  const char *str2 = "12355";
  size_t n = 5;
  int result = s21_memcmp(str1, str2, n);
  ck_assert(result < 0);
}
END_TEST

START_TEST(test_s21_memcmp_figure_greater) {
  const char *str1 = "12355";
  const char *str2 = "123456789";
  size_t n = 5;
  int result = s21_memcmp(str1, str2, n);
  ck_assert(result > 0);
}
END_TEST

START_TEST(test_s21_memcmp_letter_less) {
  const char *str1 = "abcce";
  const char *str2 = "abcde";
  size_t n = 5;
  int result = s21_memcmp(str1, str2, n);
  ck_assert(result < 0);
}
END_TEST

START_TEST(test_s21_memcmp_letter_greater) {
  const char *str1 = "abcde";
  const char *str2 = "abcce";
  size_t n = 5;
  int result = s21_memcmp(str1, str2, n);
  ck_assert(result > 0);
}
END_TEST

START_TEST(test_s21_memcmp_zero_n) {
  const char *str1 = "Hello";
  const char *str2 = "School";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), 0);
}
END_TEST

START_TEST(test_s21_memcmp_binary_not_equal) {
  unsigned char data1[] = {0x00, 0x01, 0x02, 0x03};
  unsigned char data2[] = {0x00, 0x01, 0x12, 0x03};
  size_t n = sizeof(data1);
  int result = s21_memcmp(data1, data2, n);
  ck_assert(result < 0);
}
END_TEST

START_TEST(test_s21_memcmp_binary_equal) {
  unsigned char data1[] = {0x00, 0x01, 0x02, 0x03};
  unsigned char data2[] = {0x00, 0x01, 0x02, 0x03};
  size_t n = sizeof(data1);
  ck_assert_int_eq(s21_memcmp(data1, data2, n), 0);
}
END_TEST

START_TEST(test_s21_memcpy_letter_basic) {
  char src[] = "Hello, school!";
  char dest[20] = {0};
  char dest_std[20] = {0};
  size_t len = strlen(src) + 1;

  void *res = s21_memcpy(dest, src, len);
  void *res_std = memcpy(dest_std, src, len);

  ck_assert_ptr_eq(res, dest);
  ck_assert_mem_eq(res_std, dest_std, len);
  ck_assert_mem_eq(dest, dest_std, len);
}
END_TEST

START_TEST(test_s21_memcpy_letter_partial) {
  char src[] = "Hello, school!";
  char dest[20] = {0};
  char dest_std[20] = {0};
  size_t len = strlen(src);

  void *res = s21_memcpy(dest, src, len);
  void *res_std = memcpy(dest_std, src, len);

  ck_assert_ptr_eq(res, dest);
  ck_assert_mem_eq(res_std, dest_std, len);
  ck_assert_mem_eq(dest, dest_std, len);
}
END_TEST

START_TEST(test_s21_memcpy_figure_basic) {
  int src[] = {1, 2, 3, 4, 5};
  int dest[5] = {0};
  int dest_std[5] = {0};
  size_t n = sizeof(src);

  s21_memcpy(dest, src, n);
  memcpy(dest_std, src, n);

  ck_assert_mem_eq(dest, dest_std, n);
}
END_TEST

START_TEST(test_s21_memcpy_figure_partial) {
  int src[] = {1, 2, 3, 4, 5};
  int dest[5] = {0};
  int dest_std[5] = {0};
  size_t n = 3 * sizeof(int);

  s21_memcpy(dest, src, n);
  memcpy(dest_std, src, n);

  ck_assert_mem_eq(dest, dest_std, n);
}
END_TEST

START_TEST(test_s21_memcpy_zero_bytes) {
  char src[] = "Hello";
  char dest[10] = "School";
  char dest_std[10] = "School";

  s21_memcpy(dest, src, 0);
  memcpy(dest_std, src, 0);

  ck_assert_str_eq(dest, dest_std);
}
END_TEST

START_TEST(test_memset_various) {
  char s1[10] = "abcdefghi";
  char s2[10] = "abcdefghi";
  ck_assert_str_eq(memset(s1, 'x', 9), s21_memset(s2, 'x', 9));
  ck_assert_str_eq(memset(s1, 'y', 5), s21_memset(s2, 'y', 5));
}
END_TEST

START_TEST(test_s21_memset_letter_basic) {
  char str1[20] = "Hello, school!";
  char str2[20] = "Hello, school!";
  s21_memset(str1, 'x', 5);
  memset(str2, 'x', 5);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_s21_memset_figure_basic) {
  char str1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  char str2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  unsigned char fill = '1';
  s21_memset(str1, fill, 5);
  memset(str2, fill, 5);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(test_s21_memset_letter_zero) {
  char str1[20] = "Hello, school!";
  char str2[20] = "Hello, school!";
  s21_memset(str1, 0, 5);
  memset(str2, 0, 5);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_s21_memset_figure_zero) {
  char str1[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  char str2[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21_memset(str1, 0, 5);
  memset(str2, 0, 5);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_s21_memset_letter_no_change) {
  char str1[20] = "Hello, school!";
  char str2[20] = "Hello, school!";
  size_t zero_size = 0;
  s21_memset(str1, 'x', zero_size);
  memset(str2, 'x', zero_size);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_s21_memset_figure_no_change) {
  char str1[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  char str2[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t zero_size = 0;
  s21_memset(str1, '1', zero_size);
  memset(str2, '1', zero_size);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_s21_memset_unsigned) {
  unsigned char buf1[10];
  unsigned char buf2[10];
  unsigned char fill = 0xAB;

  s21_memset(buf1, fill, 10);
  memset(buf2, fill, 10);
  ck_assert_mem_eq(buf1, buf2, 10);
}
END_TEST

START_TEST(test_s21_memset_return_letter) {
  char str[20];
  void *ret = s21_memset(str, 'a', 10);
  ck_assert_ptr_eq(ret, str);
}
END_TEST

START_TEST(test_s21_memset_return_figure) {
  char str[20];
  void *ret = s21_memset(str, '1', 10);
  ck_assert_ptr_eq(ret, str);
}
END_TEST

START_TEST(test_strncat_various) {
  char s1[20] = "a";
  char s2[20] = "a";
  ck_assert_str_eq(strncat(s1, "", 0), s21_strncat(s2, "", 0));

  char s3[20] = "abc";
  char s4[20] = "abc";
  ck_assert_str_eq(strncat(s3, "def", 2), s21_strncat(s4, "def", 2));
}
END_TEST

START_TEST(test_s21_strncat_basic) {
  char dest[50] = "Hello";
  const char src[] = " School!";
  size_t n = 8;
  char *res = s21_strncat(dest, src, n);
  ck_assert_str_eq(res, "Hello School!");
  ck_assert_ptr_eq(res, dest);
}
END_TEST

START_TEST(test_s21_strncat_partial) {
  char dest[50] = "Hello";
  const char src[] = " School!";
  size_t n = 3;
  s21_strncat(dest, src, n);
  ck_assert_str_eq(dest, "Hello Sc");
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  char dest[50] = "";
  const char src[] = "Hello";
  size_t n = 5;
  s21_strncat(dest, src, n);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_s21_strncat_empty_src) {
  char dest[50] = "Hello";
  const char src[] = "";
  size_t n = 5;
  s21_strncat(dest, src, n);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_s21_strncat_zero_n) {
  char dest[50] = "Hello";
  const char src[] = " School!";
  size_t n = 0;
  s21_strncat(dest, src, n);
  ck_assert_str_eq(dest, "Hello");
}
END_TEST

START_TEST(test_s21_strncat_larger_n) {
  char dest[50] = "Hello";
  const char src[] = " School!";
  size_t n = 10;
  s21_strncat(dest, src, n);
  ck_assert_str_eq(dest, "Hello School!");
}
END_TEST

START_TEST(test_strchr_various) {
  char str[] = "Hello, world!";
  ck_assert_ptr_eq(strchr(str, 'H'), s21_strchr(str, 'H'));
  ck_assert_ptr_eq(strchr(str, '!'), s21_strchr(str, '!'));
  ck_assert_ptr_eq(strchr(str, 'z'), s21_strchr(str, 'z'));
  ck_assert_ptr_eq(strchr(str, '\0'), s21_strchr(str, '\0'));
}
END_TEST

START_TEST(test_strncmp_various) {
  ck_assert_int_eq(strncmp("abc", "abc", 3), s21_strncmp("abc", "abc", 3));
  ck_assert_int_eq(strncmp("abc", "abd", 2), s21_strncmp("abc", "abd", 2));
  ck_assert_int_eq(strncmp("abc", "abcd", 4), s21_strncmp("abc", "abcd", 4));
  ck_assert_int_eq(strncmp("", "", 1), s21_strncmp("", "", 1));
}
END_TEST

START_TEST(test_strncpy_various) {
  char dest1[10], dest2[10];
  ck_assert_str_eq(strncpy(dest1, "abc\0", 4), s21_strncpy(dest2, "abc\0", 4));

  char dest3[10], dest4[10];
  ck_assert_str_eq(strncpy(dest3, "", 3), s21_strncpy(dest4, "", 3));

  char dest5[10], dest6[10];
  ck_assert_str_eq(strncpy(dest5, "abc", 6), s21_strncpy(dest6, "abc", 6));
}
END_TEST

START_TEST(test_strcspn_various) {
  ck_assert_uint_eq(strcspn("abcdef", "x"), s21_strcspn("abcdef", "x"));
  ck_assert_uint_eq(strcspn("abcdef", "de"), s21_strcspn("abcdef", "de"));
  ck_assert_uint_eq(strcspn("", "a"), s21_strcspn("", "a"));
}
END_TEST

START_TEST(test_strerror_all) {
  for (int i = -5; i <= 140; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(test_strlen_various) {
  ck_assert_uint_eq(strlen(""), s21_strlen(""));
  ck_assert_uint_eq(strlen("123"), s21_strlen("123"));
  ck_assert_uint_eq(
      strlen("A very very long string with spaces and 12345"),
      s21_strlen("A very very long string with spaces and 12345"));
}
END_TEST

START_TEST(test_strpbrk_various) {
  ck_assert_ptr_eq(strpbrk("abc", "x"), s21_strpbrk("abc", "x"));
  ck_assert_ptr_eq(strpbrk("abc", "c"), s21_strpbrk("abc", "c"));
  ck_assert_ptr_eq(strpbrk("abc", ""), s21_strpbrk("abc", ""));
}
END_TEST

START_TEST(test_strrchr_various) {
  ck_assert_ptr_eq(strrchr("abcabc", 'a'), s21_strrchr("abcabc", 'a'));
  ck_assert_ptr_eq(strrchr("abcabc", '\0'), s21_strrchr("abcabc", '\0'));
}
END_TEST

START_TEST(test_strstr_various) {
  ck_assert_ptr_eq(strstr("abcdef", "cd"), s21_strstr("abcdef", "cd"));
  ck_assert_ptr_eq(strstr("abcdef", "xyz"), s21_strstr("abcdef", "xyz"));
  ck_assert_ptr_eq(strstr("abcdef", ""), s21_strstr("abcdef", ""));
}
END_TEST

START_TEST(test_strtok_various) {
  char str1[] = "a,b,c";
  char str2[] = "a,b,c";
  char *t1 = strtok(str1, ",");
  char *t2 = s21_strtok(str2, ",");

  while (t1 != NULL || t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = strtok(NULL, ",");
    t2 = s21_strtok(NULL, ",");
  }

  char str3[] = "1:2:3";
  char str4[] = "1:2:3";
  t1 = strtok(str3, ":");
  t2 = s21_strtok(str4, ":");

  while (t1 != NULL || t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = strtok(NULL, ":");
    t2 = s21_strtok(NULL, ":");
  }

  char str5[] = "+-one+-two+-three=four?";
  char str6[] = "+-one+-two+-three=four?";
  t1 = strtok(str5, "+-=");
  t2 = s21_strtok(str6, "+-=");

  while (t1 != NULL || t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = strtok(NULL, "+-=");
    t2 = s21_strtok(NULL, "+-=");
  }
}
END_TEST

START_TEST(test_s21_to_upper_basic) {
  char *input = "hello, school!";
  char *expected = "HELLO, SCHOOL!";
  char *result = (char *)s21_to_upper(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  char *input = "";
  char *expected = "";
  char *result = (char *)s21_to_upper(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_only_spaces) {
  const char *input = "     ";
  char *expected = "     ";
  char *result = (char *)s21_to_upper(input);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_figure_only) {
  char *input = "123456789 !@#$";
  char *expected = "123456789 !@#$";
  char *result = (char *)s21_to_upper(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_mixed_letter_and_figure) {
  char *input = "HeLLo, SChooL! 12345";
  char *expected = "HELLO, SCHOOL! 12345";
  char *result = (char *)s21_to_upper(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_null) {
  char *result = (char *)s21_to_upper(NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_to_upper_mixed_rus_eng) {
  char *input = "Привет ours мир!";
  char *expected = "Привет OURS мир!";
  char *result = (char *)s21_to_upper(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_basic) {
  char *input = "HELLO, SCHOOL!";
  char *expected = "hello, school!";
  char *result = (char *)s21_to_lower(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  char *input = "";
  char *expected = "";
  char *result = (char *)s21_to_lower(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_only_spaces) {
  const char *input = "     ";
  char *expected = "     ";
  char *result = (char *)s21_to_lower(input);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_null) {
  char *result = (char *)s21_to_lower(NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_to_lower_figure_only) {
  char *input = "123456789 !@#$";
  char *expected = "123456789 !@#$";
  char *result = (char *)s21_to_lower(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_mixed_letter_and_figure) {
  char *input = "HeLLo, SChooL! 12345";
  char *expected = "hello, school! 12345";
  char *result = (char *)s21_to_lower(input);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_basic_1) {
  const char *src = "Hello World!";
  const char *ins = "Beautiful ";
  s21_size_t index = 6;
  char *expected = "Hello Beautiful World!";
  char *result = (char *)s21_insert(src, ins, index);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_basic_2) {
  char *res = s21_insert("Hello", " school", 5);
  ck_assert_str_eq(res, "Hello school");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_out_of_bounds) {
  const char *src = "Hello";
  const char *ins = "World";
  s21_size_t index = 100;
  char *result = (char *)s21_insert(src, ins, index);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_insert_empty_src) {
  const char *src = "";
  const char *ins = "Hello";
  char *expected = "Hello";
  char *result = (char *)s21_insert(src, ins, 0);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty_insert) {
  const char *src = "Test";
  const char *ins = "";
  char *expected = "Test";
  char *result = (char *)s21_insert(src, ins, 2);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_empty) {
  char *res = s21_insert("", "hello", 0);
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_null_src) {
  const char *ins = "Hello";
  char *result = (char *)s21_insert(NULL, ins, 0);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_insert_null_insert) {
  const char *src = "Hello";
  char *result = (char *)s21_insert(src, NULL, 0);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_insert_error) {
  ck_assert_ptr_null(s21_insert(NULL, "hello", 0));
  ck_assert_ptr_null(s21_insert("hello", NULL, 0));
  ck_assert_ptr_null(s21_insert("hello", "school", 10));
}
END_TEST

START_TEST(test_s21_trim_basic_1) {
  const char *src = "   Hello, School!   ";
  const char *trim_chars = " ";
  char *expected = "Hello, School!";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_basic_2) {
  char *res = s21_trim("  hello  ", NULL);
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_custom_chars) {
  const char *src = "xxxyTest stringyyy";
  const char *trim_chars = "xy";
  char *expected = "Test string";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_two_zets) {
  char *res = s21_trim("zzhellozz", "z");
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_empty_src) {
  const char *src = "";
  const char *trim_chars = " ";
  char *expected = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty) {
  char *res = s21_trim("", NULL);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_only_spaces) {
  const char *src = "     ";
  const char *trim_chars = " ";
  char *expected = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_null_src_1) {
  const char *trim_chars = " ";
  char *result = s21_trim(NULL, trim_chars);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_trim_null_src_2) {
  void *res = s21_trim(NULL, "xyz");
  ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_s21_trim_null_trim_chars) {
  const char *src = "  Hello  ";
  char *result = s21_trim(src, NULL);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_all_trimmed) {
  char *res = s21_trim("zzz", "z");
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_no_trim) {
  char *res = s21_trim("hello", "abc");
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

Suite *string_suite(void) {
  Suite *s = suite_create("s21_string");

  TCase *tc_memchr = tcase_create("memchr");
  tcase_add_test(tc_memchr, test_memchr_various);
  tcase_add_test(tc_memchr, test_s21_memchr_basic);
  tcase_add_test(tc_memchr, test_s21_memchr_not_found);
  tcase_add_test(tc_memchr, test_s21_memchr_zero_length);
  tcase_add_test(tc_memchr, test_s21_memchr_partial);
  tcase_add_test(tc_memchr, test_s21_memchr_binary_found);
  tcase_add_test(tc_memchr, test_s21_memchr_binary_not_found);
  suite_add_tcase(s, tc_memchr);

  TCase *tc_memcmp = tcase_create("memcmp");
  tcase_add_test(tc_memcmp, test_memcmp_various);
  tcase_add_test(tc_memcmp, test_s21_memcmp_equal);
  tcase_add_test(tc_memcmp, test_s21_memcmp_not_equal);
  tcase_add_test(tc_memcmp, test_s21_memcmp_figure_less);
  tcase_add_test(tc_memcmp, test_s21_memcmp_figure_greater);
  tcase_add_test(tc_memcmp, test_s21_memcmp_letter_less);
  tcase_add_test(tc_memcmp, test_s21_memcmp_letter_greater);
  tcase_add_test(tc_memcmp, test_s21_memcmp_zero_n);
  tcase_add_test(tc_memcmp, test_s21_memcmp_binary_not_equal);
  tcase_add_test(tc_memcmp, test_s21_memcmp_binary_equal);
  suite_add_tcase(s, tc_memcmp);

  TCase *tc_memcpy = tcase_create("memcpy");
  tcase_add_test(tc_memcpy, test_s21_memcpy_letter_basic);
  tcase_add_test(tc_memcpy, test_s21_memcpy_letter_partial);
  tcase_add_test(tc_memcpy, test_s21_memcpy_figure_basic);
  tcase_add_test(tc_memcpy, test_s21_memcpy_figure_partial);
  tcase_add_test(tc_memcpy, test_s21_memcpy_zero_bytes);
  suite_add_tcase(s, tc_memcpy);

  TCase *tc_memset = tcase_create("memset");
  tcase_add_test(tc_memset, test_memset_various);
  tcase_add_test(tc_memset, test_s21_memset_letter_basic);
  tcase_add_test(tc_memset, test_s21_memset_figure_basic);
  tcase_add_test(tc_memset, test_s21_memset_letter_zero);
  tcase_add_test(tc_memset, test_s21_memset_figure_zero);
  tcase_add_test(tc_memset, test_s21_memset_letter_no_change);
  tcase_add_test(tc_memset, test_s21_memset_figure_no_change);
  tcase_add_test(tc_memset, test_s21_memset_unsigned);
  tcase_add_test(tc_memset, test_s21_memset_return_letter);
  tcase_add_test(tc_memset, test_s21_memset_return_figure);
  suite_add_tcase(s, tc_memset);

  TCase *tc_strncat = tcase_create("strncat");
  tcase_add_test(tc_strncat, test_strncat_various);
  tcase_add_test(tc_strncat, test_s21_strncat_basic);
  tcase_add_test(tc_strncat, test_s21_strncat_partial);
  tcase_add_test(tc_strncat, test_s21_strncat_empty_dest);
  tcase_add_test(tc_strncat, test_s21_strncat_empty_src);
  tcase_add_test(tc_strncat, test_s21_strncat_zero_n);
  tcase_add_test(tc_strncat, test_s21_strncat_larger_n);
  suite_add_tcase(s, tc_strncat);

  TCase *tc_strchr = tcase_create("strchr");
  tcase_add_test(tc_strchr, test_strchr_various);
  suite_add_tcase(s, tc_strchr);

  TCase *tc_strncmp = tcase_create("strncmp");
  tcase_add_test(tc_strncmp, test_strncmp_various);
  suite_add_tcase(s, tc_strncmp);

  TCase *tc_strncpy = tcase_create("strncpy");
  tcase_add_test(tc_strncpy, test_strncpy_various);
  suite_add_tcase(s, tc_strncpy);

  TCase *tc_strcspn = tcase_create("strcspn");
  tcase_add_test(tc_strcspn, test_strcspn_various);
  suite_add_tcase(s, tc_strcspn);

  TCase *tc_strerror = tcase_create("strerror");
  tcase_add_test(tc_strerror, test_strerror_all);
  suite_add_tcase(s, tc_strerror);

  TCase *tc_strlen = tcase_create("strlen");
  tcase_add_test(tc_strlen, test_strlen_various);
  suite_add_tcase(s, tc_strlen);

  TCase *tc_strpbrk = tcase_create("strpbrk");
  tcase_add_test(tc_strpbrk, test_strpbrk_various);
  suite_add_tcase(s, tc_strpbrk);

  TCase *tc_strrchr = tcase_create("strrchr");
  tcase_add_test(tc_strrchr, test_strrchr_various);
  suite_add_tcase(s, tc_strrchr);

  TCase *tc_strstr = tcase_create("strstr");
  tcase_add_test(tc_strstr, test_strstr_various);
  suite_add_tcase(s, tc_strstr);

  TCase *tc_strtok = tcase_create("strtok");
  tcase_add_test(tc_strtok, test_strtok_various);
  suite_add_tcase(s, tc_strtok);

  TCase *tc_upper = tcase_create("to_upper");
  tcase_add_test(tc_upper, test_s21_to_upper_basic);
  tcase_add_test(tc_upper, test_s21_to_upper_empty);
  tcase_add_test(tc_upper, test_s21_to_upper_only_spaces);
  tcase_add_test(tc_upper, test_s21_to_upper_null);
  tcase_add_test(tc_upper, test_s21_to_upper_figure_only);
  tcase_add_test(tc_upper, test_s21_to_upper_mixed_letter_and_figure);
  tcase_add_test(tc_upper, test_s21_to_upper_mixed_rus_eng);

  suite_add_tcase(s, tc_upper);

  TCase *tc_lower = tcase_create("to_lower");
  tcase_add_test(tc_lower, test_s21_to_lower_basic);
  tcase_add_test(tc_lower, test_s21_to_lower_empty);
  tcase_add_test(tc_lower, test_s21_to_lower_only_spaces);
  tcase_add_test(tc_lower, test_s21_to_lower_null);
  tcase_add_test(tc_lower, test_s21_to_lower_figure_only);
  tcase_add_test(tc_lower, test_s21_to_lower_mixed_letter_and_figure);
  suite_add_tcase(s, tc_lower);

  TCase *tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, test_s21_insert_basic_1);
  tcase_add_test(tc_insert, test_s21_insert_basic_2);
  tcase_add_test(tc_insert, test_s21_insert_out_of_bounds);
  tcase_add_test(tc_insert, test_s21_insert_empty_src);
  tcase_add_test(tc_insert, test_s21_insert_empty_insert);
  tcase_add_test(tc_insert, test_s21_insert_empty);
  tcase_add_test(tc_insert, test_s21_insert_null_src);
  tcase_add_test(tc_insert, test_s21_insert_null_insert);
  tcase_add_test(tc_insert, test_s21_insert_error);
  suite_add_tcase(s, tc_insert);

  TCase *tc_trim = tcase_create("trim");
  tcase_add_test(tc_trim, test_s21_trim_basic_1);
  tcase_add_test(tc_trim, test_s21_trim_basic_2);
  tcase_add_test(tc_trim, test_s21_trim_custom_chars);
  tcase_add_test(tc_trim, test_s21_trim_two_zets);
  tcase_add_test(tc_trim, test_s21_trim_empty_src);
  tcase_add_test(tc_trim, test_s21_trim_empty);
  tcase_add_test(tc_trim, test_s21_trim_only_spaces);
  tcase_add_test(tc_trim, test_s21_trim_null_src_1);
  tcase_add_test(tc_trim, test_s21_trim_null_src_2);
  tcase_add_test(tc_trim, test_s21_trim_null_trim_chars);
  tcase_add_test(tc_trim, test_s21_trim_all_trimmed);
  tcase_add_test(tc_trim, test_s21_trim_no_trim);
  suite_add_tcase(s, tc_trim);

  return s;
}
