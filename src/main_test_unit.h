#ifndef MAIN_TEST_UNIT_H
#define MAIN_TEST_UNIT_H

#define _POSIX_C_SOURCE 200112L
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *s21_sprintf_suite(void);
Suite *string_suite(void);
Suite *s21_sscanf_suite(void);

#endif
