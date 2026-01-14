#include "s21_sprintf.h"

#include <math.h>
#include <stdarg.h>
#include <stdint.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  if (!str || !format) return -1;
  s21_sprintf_state state = {str, 0, MAX_BUFFER_SIZE, S21_NULL};
  va_list args;
  va_start(args, format);
  state.args = &args;
  for (const char *format_ptr = format; *format_ptr; ++format_ptr) {
    if (*format_ptr != '%') {
      add_char(&state, *format_ptr);
    } else {
      format_specifier frmt_spcfr = {0};
      frmt_spcfr.precision = -1;
      ++format_ptr;
      if (!*format_ptr) break;
      parse_flags(&format_ptr, &frmt_spcfr);
      parse_width(&format_ptr, &frmt_spcfr, &args);
      parse_precision(&format_ptr, &frmt_spcfr, &args);
      parse_length(&format_ptr, &frmt_spcfr);
      switch (*format_ptr) {
        SHORT_HANDLE_SPECIFIER('c', c_specifier);
        SHORT_HANDLE_SPECIFIER('d', d_specifier);
        SHORT_HANDLE_SPECIFIER('i', d_specifier);
        SHORT_HANDLE_SPECIFIER('u', u_specifier);
        SHORT_HANDLE_SPECIFIER('o', o_specifier);
        HANDLE_SPECIFIER('x', x_specifier);
        HANDLE_SPECIFIER('X', x_specifier);
        SHORT_HANDLE_SPECIFIER('p', p_specifier);
        SHORT_HANDLE_SPECIFIER('f', f_specifier);
        HANDLE_SPECIFIER('e', e_specifier);
        HANDLE_SPECIFIER('E', e_specifier);
        HANDLE_SPECIFIER('g', g_specifier);
        HANDLE_SPECIFIER('G', g_specifier);
        SHORT_HANDLE_SPECIFIER('s', s_specifier);
        case '%':
          add_char(&state, '%');
          break;
      }
    }
  }
  if (state.current_len >= state.max_len) state.current_len = state.max_len - 1;
  state.output[state.current_len] = '\0';
  va_end(args);
  return (int)state.current_len;
}

void parse_flags(const char **format_ptr, format_specifier *frmt_spcfr) {
  while (**format_ptr == '-' || **format_ptr == '+' || **format_ptr == ' ' ||
         **format_ptr == '0' || **format_ptr == '#') {
    if (**format_ptr == '-') frmt_spcfr->left_align = 1;
    if (**format_ptr == '+') frmt_spcfr->show_sign = 1;
    if (**format_ptr == ' ') frmt_spcfr->space = 1;
    if (**format_ptr == '0') frmt_spcfr->zero_pad = 1;
    if (**format_ptr == '#') frmt_spcfr->sharp = 1;
    ++(*format_ptr);
  }
}

void parse_width(const char **format_ptr, format_specifier *frmt_spcfr,
                 va_list *args) {
  if (**format_ptr == '*') {
    frmt_spcfr->width = va_arg(*args, int);
    ++(*format_ptr);
  } else {
    while (**format_ptr >= '0' && **format_ptr <= '9') {
      frmt_spcfr->width = frmt_spcfr->width * 10 + (**format_ptr - '0');
      ++(*format_ptr);
    }
  }
}

void parse_precision(const char **format_ptr, format_specifier *frmt_spcfr,
                     va_list *args) {
  if (**format_ptr == '.') {
    ++(*format_ptr);
    frmt_spcfr->precision = 0;
    if (**format_ptr == '*') {
      frmt_spcfr->precision = va_arg(*args, int);
      ++(*format_ptr);
    } else {
      while (**format_ptr >= '0' && **format_ptr <= '9') {
        frmt_spcfr->precision =
            frmt_spcfr->precision * 10 + (**format_ptr - '0');
        ++(*format_ptr);
      }
    }
  }
}

void parse_length(const char **format_ptr, format_specifier *frmt_spcfr) {
  switch (**format_ptr) {
    case 'h':
      frmt_spcfr->h = 1;
      break;
    case 'l':
      frmt_spcfr->l = 1;
      break;
    case 'L':
      frmt_spcfr->L = 1;
      break;
    default:
      return;
  }
  ++(*format_ptr);
}

void c_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  char c = (char)va_arg(*state->args, int);
  int pad_cnt = frmt_spcfr->width > 1 ? frmt_spcfr->width - 1 : 0;
  if (!frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
  add_char(state, c);
  if (frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
}

void s_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  const char *s = va_arg(*state->args, const char *);
  if (!s) s = "(null)";
  s21_size_t len = s21_strlen(s);
  if (frmt_spcfr->precision >= 0 && (s21_size_t)frmt_spcfr->precision < len)
    len = frmt_spcfr->precision;

  int pad_cnt = frmt_spcfr->width > (int)len ? frmt_spcfr->width - (int)len : 0;
  if (!frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
  add_str(state, s, len);
  if (frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
}

void d_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  long long value;
  if (frmt_spcfr->h)
    value = (short)va_arg(*state->args, int);
  else if (frmt_spcfr->l)
    value = va_arg(*state->args, long);
  else
    value = va_arg(*state->args, int);
  add_int(value, 0, 0, 10, frmt_spcfr, state, 1);
}

void u_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  unsigned long long value;
  if (frmt_spcfr->h)
    value = (unsigned short)va_arg(*state->args, unsigned int);
  else if (frmt_spcfr->l)
    value = va_arg(*state->args, unsigned long);
  else
    value = va_arg(*state->args, unsigned int);
  add_int(0, value, 1, 10, frmt_spcfr, state, 1);
}

void o_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  unsigned long long value = va_arg(*state->args, unsigned long long);
  add_int(0, value, 1, 8, frmt_spcfr, state, 1);
}

void x_specifier(const char *format_ptr, format_specifier *frmt_spcfr,
                 s21_sprintf_state *state) {
  unsigned long long value = va_arg(*state->args, unsigned long long);
  frmt_spcfr->x = (*format_ptr == 'x');
  add_int(0, value, 1, 16, frmt_spcfr, state, frmt_spcfr->x);
}

void p_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  void *ptr = va_arg(*state->args, void *);
  if (ptr == S21_NULL) {
    const char *nil = "(nil)";
    s21_size_t len = 5;
    int cnt_pad =
        frmt_spcfr->width > (int)len ? frmt_spcfr->width - (int)len : 0;
    if (!frmt_spcfr->left_align) add_pad(state, ' ', cnt_pad);
    add_str(state, nil, len);
    if (frmt_spcfr->left_align) add_pad(state, ' ', cnt_pad);
  } else {
    frmt_spcfr->x = 1;
    frmt_spcfr->sharp = 1;
    unsigned long long value = (uintptr_t)ptr;
    add_int(0, value, 1, 16, frmt_spcfr, state, 1);
  }
}

void f_specifier(format_specifier *frmt_spcfr, s21_sprintf_state *state) {
  long double value = frmt_spcfr->L ? va_arg(*state->args, long double)
                                    : va_arg(*state->args, double);

  add_float(value, frmt_spcfr, state);
}

void e_specifier(const char *format_ptr, format_specifier *frmt_spcfr,
                 s21_sprintf_state *state) {
  int upper = (*format_ptr == 'E');
  long double value = frmt_spcfr->L ? va_arg(*state->args, long double)
                                    : va_arg(*state->args, double);
  add_exp(value, frmt_spcfr, upper, state);
}

void g_specifier(const char *format_ptr, format_specifier *frmt_spcfr,
                 s21_sprintf_state *state) {
  int upper = (*format_ptr == 'G');
  long double value = frmt_spcfr->L ? va_arg(*state->args, long double)
                                    : va_arg(*state->args, double);
  add_e_or_f(value, frmt_spcfr, upper, state);
}

s21_size_t add_prefix(const str_number *num, const format_specifier *frmt_spcfr,
                      s21_sprintf_state *state) {
  s21_size_t len = 0;
  if (!num->is_unsigned) {
    char sign = 0;
    if (num->is_negative)
      sign = '-';
    else if (frmt_spcfr->show_sign)
      sign = '+';
    else if (frmt_spcfr->space)
      sign = ' ';
    if (sign) {
      if (state) add_char(state, sign);
      ++len;
    }
  }

  if (frmt_spcfr->sharp && !num->is_zero) {
    if (num->base == 16) {
      if (state) {
        add_char(state, '0');
        add_char(state, frmt_spcfr->x ? 'x' : 'X');
      }
      len += 2;
    } else if (num->base == 8) {
      if (state) add_char(state, '0');
      ++len;
    }
  }
  return len;
}

void add_int(long long v_signed, unsigned long long v_unsigned, int is_unsigned,
             int base, format_specifier *frmt_spcfr, s21_sprintf_state *state,
             int lower) {
  char buf[MAX_NUMBER_LENGTH];
  str_number num = {buf, base, is_unsigned, 0, 0};
  unsigned long long u = is_unsigned
                             ? v_unsigned
                             : (v_signed < 0 ? -(unsigned long long)v_signed
                                             : (unsigned long long)v_signed);
  convert_utoa(u, base, lower, buf);
  num.is_negative = (!is_unsigned && v_signed < 0);
  num.is_zero = (u == 0);
  s21_size_t digits = s21_strlen(buf);
  s21_size_t zeros =
      (frmt_spcfr->precision >= 0 && frmt_spcfr->precision > (int)digits)
          ? frmt_spcfr->precision - digits
          : 0;
  if (frmt_spcfr->precision >= 0) frmt_spcfr->zero_pad = 0;

  s21_size_t prefix_len = add_prefix(&num, frmt_spcfr, S21_NULL);

  s21_size_t total = prefix_len + zeros + digits;
  int pad_cnt =
      frmt_spcfr->width > (int)total ? frmt_spcfr->width - (int)total : 0;

  if (!frmt_spcfr->left_align && !frmt_spcfr->zero_pad)
    add_pad(state, ' ', pad_cnt);
  add_prefix(&num, frmt_spcfr, state);
  if (!frmt_spcfr->left_align && frmt_spcfr->zero_pad)
    add_pad(state, '0', pad_cnt);
  add_pad(state, '0', (int)zeros);
  add_str(state, buf, digits);
  if (frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
}

void add_float(long double value, format_specifier *frmt_spcfr,
               s21_sprintf_state *state) {
  if (add_inf_or_nan(value, 0, frmt_spcfr, state)) return;
  int precision = (frmt_spcfr->precision < 0) ? 6 : frmt_spcfr->precision;
  if (precision > MAX_PRECISION) precision = MAX_PRECISION;
  int neg = (value < 0.0L) || (value == 0.0L && signbit(value));
  if (neg) value = -value;
  char tmp[MAX_TMP_SIZE];
  s21_float_to_str(value, tmp, precision);
  if (precision == 0 && frmt_spcfr->sharp) {
    s21_size_t len = s21_strlen(tmp);
    tmp[len] = '.';
    tmp[len + 1] = '\0';
  }
  char sign = 0;
  if (neg)
    sign = '-';
  else if (frmt_spcfr->show_sign)
    sign = '+';
  else if (frmt_spcfr->space)
    sign = ' ';
  s21_size_t num_len = s21_strlen(tmp);
  s21_size_t total = num_len + (sign ? 1 : 0);
  int pad_cnt =
      frmt_spcfr->width > (int)total ? frmt_spcfr->width - (int)total : 0;
  char pad_char = (frmt_spcfr->zero_pad && !frmt_spcfr->left_align) ? '0' : ' ';
  if (!frmt_spcfr->left_align && pad_char == ' ')
    add_pad(state, pad_char, pad_cnt);
  if (sign) add_char(state, sign);
  if (!frmt_spcfr->left_align && pad_char == '0')
    add_pad(state, pad_char, pad_cnt);
  add_str(state, tmp, num_len);
  if (frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
}
void normalize10(long double *pv, int *pexp) {
  long double value = *pv;
  int e = 0;
  if (value) {
    while (fabsl(value) >= 10.0L) {
      value /= 10.0L;
      ++e;
    }
    while (fabsl(value) < 1.0L) {
      value *= 10.0L;
      --e;
    }
  }
  *pv = value;
  *pexp = e;
}

void add_exp(long double value, format_specifier *frmt_spcfr, int upper,
             s21_sprintf_state *state) {
  if (add_inf_or_nan(value, upper, frmt_spcfr, state)) return;
  int precision = (frmt_spcfr->precision < 0) ? 6 : frmt_spcfr->precision;
  if (precision > MAX_PRECISION) precision = MAX_PRECISION;
  int neg = (value < 0.0L);
  if (neg) value = -value;
  int exp10 = 0;
  normalize10(&value, &exp10);
  long double pow10 = 1.0L;
  for (int i = 0; i < precision; ++i) pow10 *= 10.0L;
  unsigned long long int_m = (unsigned long long)(value * pow10 + 0.5L);
  if (int_m / (unsigned long long)pow10 >= 10ULL) {
    int_m /= 10;
    ++exp10;
  }
  long double mant = (long double)int_m / pow10;
  char buf[MAX_TMP_SIZE], *ptr = buf;
  if (neg)
    *ptr++ = '-';
  else if (frmt_spcfr->show_sign)
    *ptr++ = '+';
  else if (frmt_spcfr->space)
    *ptr++ = ' ';
  *ptr++ = (char)('0' + (int)mant);
  if (precision || frmt_spcfr->sharp) *ptr++ = '.';
  long double frac = mant - (int)mant;
  for (int i = 0; i < precision; ++i) {
    frac *= 10.0L;
    int d = (int)frac;
    *ptr++ = (char)('0' + d);
    frac -= d;
  }
  *ptr++ = upper ? 'E' : 'e';
  *ptr++ = (exp10 >= 0) ? '+' : '-';
  if (exp10 < 0) exp10 = -exp10;
  if (exp10 >= 100) *ptr++ = (char)('0' + (exp10 / 100) % 10);
  *ptr++ = (char)('0' + (exp10 / 10) % 10);
  *ptr++ = (char)('0' + (exp10 % 10));
  *ptr = '\0';
  s21_size_t len = s21_strlen(buf);
  int pad_cnt = frmt_spcfr->width > (int)len ? frmt_spcfr->width - (int)len : 0;
  char pad_c = (frmt_spcfr->zero_pad && !frmt_spcfr->left_align) ? '0' : ' ';
  if (!frmt_spcfr->left_align) add_pad(state, pad_c, pad_cnt);
  add_str(state, buf, len);
  if (frmt_spcfr->left_align) add_pad(state, ' ', pad_cnt);
}

void add_e_or_f(long double value, format_specifier *frmt_spcfr, int upper,
                s21_sprintf_state *state) {
  if (add_inf_or_nan(value, upper, frmt_spcfr, state)) return;

  int precision = (frmt_spcfr->precision < 0) ? 6 : frmt_spcfr->precision;
  if (precision == 0) precision = 1;

  long double tmp = fabsl(value);
  int e = 0;
  normalize10(&tmp, &e);
  int exp_fmt = (e < -4 || e >= precision);

  format_specifier loc = *frmt_spcfr;
  loc.sharp = 1;
  char buf[MAX_TMP_SIZE];
  s21_sprintf_state tmp_st = {buf, 0, sizeof(buf), state->args};

  if (exp_fmt) {
    loc.precision = precision - 1;
    add_exp(value, &loc, upper, &tmp_st);
  } else {
    loc.precision = precision - (e + 1);
    if (loc.precision < 0) loc.precision = 0;
    add_float(value, &loc, &tmp_st);
  }
  if (!frmt_spcfr->sharp) {
    char *dot = s21_strchr(buf, '.');
    if (dot) {
      char *end = buf + tmp_st.current_len - 1;
      while (end > dot && *end == '0') --end;
      if (*end == '.') --end;
      tmp_st.current_len = end - buf + 1;
      buf[tmp_st.current_len] = '\0';
    }
  }
  add_str(state, buf, tmp_st.current_len);
}

void add_str(s21_sprintf_state *state, const char *s, s21_size_t len) {
  if (state->current_len + len >= state->max_len)
    len = state->max_len - state->current_len - 1;
  s21_strncpy(state->output + state->current_len, s, len);
  state->current_len += len;
}

void add_char(s21_sprintf_state *state, char c) {
  if (state->current_len + 1 < state->max_len)
    state->output[state->current_len++] = c;
}

void add_pad(s21_sprintf_state *state, char ch, int cnt) {
  for (int i = 0; i < cnt; ++i) add_char(state, ch);
}

int add_inf_or_nan(long double value, int upper, format_specifier *frmt_spcfr,
                   s21_sprintf_state *state) {
  int result = 0;

  if (s21_isnan(value)) {
    add_str(state, upper ? "NAN" : "nan", 3);
    result = 1;
  } else if (s21_isinf(value)) {
    if (value < 0)
      add_char(state, '-');
    else if (frmt_spcfr->show_sign)
      add_char(state, '+');
    else if (frmt_spcfr->space)
      add_char(state, ' ');
    add_str(state, upper ? "INF" : "inf", 3);
    result = 1;
  }

  return result;
}

void convert_utoa(unsigned long long value, int base, int lower, char *buf) {
  static const char lo[] = "0123456789abcdef";
  static const char up[] = "0123456789ABCDEF";
  const char *dig = lower ? lo : up;
  int i = 0;
  if (value == 0) buf[i++] = '0';
  while (value) {
    buf[i++] = dig[value % base];
    value /= base;
  }
  buf[i] = '\0';
  for (int l = 0, r = i - 1; l < r; l++, r--) {
    char t = buf[l];
    buf[l] = buf[r];
    buf[r] = t;
  }
}

char *s21_utoa_base(unsigned long value, char *buffer, int base, int lower) {
  convert_utoa(value, base, lower, buffer);
  return buffer;
}

char *s21_float_to_str(long double value, char *buffer, int precision) {
  if (precision < 0) precision = 0;
  char *ptr = buffer;
  int neg = (value < 0.0L) || (value == 0.0L && signbit(value));
  if (neg) {
    *ptr++ = '-';
    value = -value;
  }

  long double rounding = 0.5L;
  for (int i = 0; i < precision; ++i) rounding /= 10.0L;
  value += rounding;
  unsigned long long int_part = (unsigned long long)value;
  long double fractional = value - (long double)int_part;
  char int_buf[MAX_NUMBER_LENGTH];
  if (int_part == 0) {
    int_buf[0] = '0';
    int_buf[1] = '\0';
  } else
    s21_utoa_base(int_part, int_buf, 10, 1);
  s21_size_t int_len = s21_strlen(int_buf);
  s21_strncpy(ptr, int_buf, int_len);
  ptr += int_len;
  if (precision > 0) {
    *ptr++ = '.';
    for (int i = 0; i < precision; ++i) {
      fractional *= 10.0L;
      int digit = (int)fractional;
      *ptr++ = '0' + digit;
      fractional -= digit;
    }
  }
  *ptr = '\0';
  return buffer;
}

int s21_isnan(long double x) { return x != x; }
int s21_isinf(long double x) { return x == S21_INFINITY || x == -S21_INFINITY; }
