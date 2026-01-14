#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

#include "s21_string.h"

typedef struct {
  char *tmp;
  int base;
  int is_unsigned;
  int is_negative;
  int is_zero;
} str_number;

typedef struct {
  char *output;
  s21_size_t current_len;
  s21_size_t max_len;
  va_list *args;
} s21_sprintf_state;

typedef struct {
  unsigned left_align : 1;
  unsigned show_sign : 1;
  unsigned space : 1;
  unsigned zero_pad : 1;
  unsigned sharp : 1;
  unsigned h : 1;
  unsigned l : 1;
  unsigned L : 1;
  unsigned x : 1;
  int width;
  int precision;
} format_specifier;

#define MAX_BUFFER_SIZE 4096
#define MAX_PRECISION 64
#define MAX_TMP_SIZE 256
#define MAX_NUMBER_LENGTH 64
#define S21_INFINITY INFINITY

#define HANDLE_SPECIFIER(spec, func)       \
  case spec:                               \
    func(format_ptr, &frmt_spcfr, &state); \
    break

#define SHORT_HANDLE_SPECIFIER(spec, func) \
  case spec:                               \
    func(&frmt_spcfr, &state);             \
    break

void parse_flags(const char **format_ptr, format_specifier *frmt_spcfr);
void parse_width(const char **format_ptr, format_specifier *frmt_spcfr,
                 va_list *args);
void parse_precision(const char **format_ptr, format_specifier *frmt_spcfr,
                     va_list *args);
void parse_length(const char **format_ptr, format_specifier *frmt_spcfr);

void c_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);
void d_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);
void e_specifier(const char *format_ptr, format_specifier *frmt_spcfr,
                 s21_sprintf_state *state);

void f_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);
void g_specifier(const char *format_ptr, format_specifier *frmt_spcfr,
                 s21_sprintf_state *state);

void o_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);
void s_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);

void u_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);
void x_specifier(const char *format_ptr, format_specifier *frmt_spcfr,
                 s21_sprintf_state *state);

void p_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state);

int s21_isnan(long double x);
int s21_isinf(long double x);

char *s21_utoa_base(unsigned long value, char *buffer, int base, int lower);
char *s21_float_to_str(long double value, char *buffer, int precision);

void add_str(s21_sprintf_state *, const char *, s21_size_t);
void add_char(s21_sprintf_state *, char);
void add_pad(s21_sprintf_state *, char, int);

int add_inf_or_nan(long double, int upper, format_specifier *,
                   s21_sprintf_state *);
void convert_utoa(unsigned long long, int base, int lower, char *);

void add_int(long long v_signed, unsigned long long v_unsigned, int is_unsigned,
             int base, format_specifier *, s21_sprintf_state *, int lower);

void add_float(long double, format_specifier *, s21_sprintf_state *);
void add_exp(long double, format_specifier *, int upper, s21_sprintf_state *);
void add_e_or_f(long double, format_specifier *, int upper,
                s21_sprintf_state *);

#endif