#include "s21_sscanf.h"

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  const char *str_start = str;
  int count = 0;
  int result = 0;
  if (check_initial_conditions(str, format) == -1) {
    result = -1;
  } else {
    while ((*format && *str) ||
           (*format == ' ' && *(format + 1) == '%' && *(format + 2) == 'n') ||
           (*format == '%' && *(format + 1) == 'n')) {
      if ((*format == ' ' && *(format + 1) == '%' && *(format + 2) == 'n') ||
          (*format == '%' && *(format + 1) == 'n')) {
        s21_specifier_n(args, str_start, str);
        format += 3;
        break;
      }
      handle_spaces(&format, &str);
      int char_result = handle_regular_char(&format, &str);
      if (char_result == 1) {
        break;
      } else if (char_result == 2) {
        if (process_specifier(&format, &str, args, &count, str_start) == -1) {
          result = count;
          break;
        }
      }
    }
  }
  va_end(args);
  return (result == -1) ? result : count;
}

int check_initial_conditions(const char *str, const char *format) {
  int result = 0;
  if (!str || !format || *str == '\0') {
    result = -1;
  }
  return result;
}

void handle_spaces(const char **format, const char **str) {
  if (s21_isspace(**format)) {
    while (s21_isspace(**str)) (*str)++;
    while (s21_isspace(**format)) (*format)++;
  }
}

int handle_regular_char(const char **format, const char **str) {
  int result = 0;
  if (**format != '%') {
    if (**format != **str) {
      result = 1;
    } else {
      (*format)++;
      (*str)++;
    }
  } else {
    result = 2;
  }
  return result;
}
int process_specifier(const char **format, const char **str, va_list args,
                      int *count, const char *str_start) {
  int result = 0;
  (*format)++;
  int skip = 0, width = 0, modifier = 0;
  search_modifier(format, &skip, &width, &modifier);
  switch (**format) {
    case 'c':
      *count += s21_specifier_c(args, str, skip, width, modifier);
      break;
    case 'd':
      *count += s21_specifier_d(args, str, skip, width, modifier);
      break;
    case 'i':
      *count += s21_specifier_i(args, str, skip, width, modifier);
      break;
    case 'u':
      *count += s21_specifier_u(args, str, skip, width, modifier);
      break;
    case 'n':
      s21_specifier_n(args, str_start, *str);
      break;
    case '%':
      if (**str == '%') {
        (*str)++;
      } else {
        result = -1;
      }
      break;
    case 'G':
    case 'g':
    case 'F':
    case 'f':
    case 'E':
    case 'e':
      *count += s21_specifier_e_E_f_F_g_G(args, str, skip, width, modifier);
      break;
    case 'o':
      *count += s21_specifier_o(args, str, skip, width, modifier);
      break;
    case 'X':
    case 'x':
      *count += s21_specifier_x_X(args, str, skip, width, modifier);
      break;
    case 's':
      *count += s21_specifier_s(args, str, skip, width);
      break;
    case 'p': {
      int p_count = s21_specifier_p(args, str, skip, width);
      if (**str == '\0' && **format != '\0' && *(*format + 1) != '\0' && skip) {
        result = -1;
      } else {
        *count += p_count;
      }
      break;
    }
  }
  if (result != -1) {
    (*format)++;
  }
  return result;
}

void search_modifier(const char **format, int *skip, int *width,
                     int *modifier) {
  const char *fmt = *format;

  while (*fmt == '*' || s21_isdigit(*fmt) || *fmt == 'l' || *fmt == 'h' ||
         *fmt == 'L') {
    if (*fmt == '*') {
      *skip = 1;
    } else if (*fmt == 'h') {
      *modifier = 'h';
    } else if (*fmt == 'l') {
      *modifier = 'l';
    } else if (*fmt == 'L') {
      *modifier = 'L';
    } else if (s21_isdigit(*fmt)) {
      *width = *width * 10 + (*fmt - '0');
    }
    fmt++;
  }

  *format = fmt;
}
int s21_isspace(int c) {
  unsigned char ch = (unsigned char)c;

  return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' ||
          ch == '\r');
}
int s21_isdigit(int c) {
  unsigned char ch = (unsigned char)c;
  return (ch >= '0' && ch <= '9');
}
int s21_isxdigit(int c) {
  unsigned char ch = (unsigned char)c;

  return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') ||
         (ch >= 'a' && ch <= 'f');
}
int s21_tolower(int c) {
  unsigned char ch = (unsigned char)c;
  if (ch >= 'A' && ch <= 'Z') {
    return ch + 32;
  }
  return ch;
}
int s21_isoct(int c) {
  unsigned char ch = (unsigned char)c;
  return (ch >= '0' && ch <= '7');
}

int s21_specifier_c(va_list args, const char **str_ptr, int skip, int width,
                    int is_long) {
  const char *str = *str_ptr;
  int count = 0;
  if (width == 0) width = 1;

  if (!is_long) {
    if (!skip) {
      char *ptr = va_arg(args, char *);
      for (int i = 0; i < width && *str; i++) {
        ptr[i] = *str++;
      }
      count++;
    } else {
      str += width;
    }
  }

  *str_ptr = str;
  return count;
}
int s21_specifier_d(va_list args, const char **str_ptr, int skip, int width,
                    int modifier) {
  const char *str = *str_ptr;
  int count = 0;
  int sign = 1;
  long num = 0;
  int digits_found = 0;
  int overflow = 0;
  int chars_processed = 0;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    if (!digits_found) {
      return -1;
    }
  }

  if (width != 1 && (*str == '-' || *str == '+')) {
    sign = (*str == '-') ? -1 : 1;
    str++;
    chars_processed++;
    if (width > 0) width--;
  }

  if (width > 0) {
    while (width-- > 0 && s21_isdigit(*str)) {
      int digit = *str++ - '0';
      digits_found = 1;
      chars_processed++;
      num = num * 10 + digit;
    }
  } else if (width == 0) {
    while (s21_isdigit(*str)) {
      int digit = *str++ - '0';
      digits_found = 1;
      chars_processed++;
      if (num > LONG_MAX / 10 ||
          (num == LONG_MAX / 10 && digit > LONG_MAX % 10)) {
        overflow = 1;
        while ((width == 0 || width-- > 0) && s21_isdigit(*str)) {
          str++;
          chars_processed++;
        }
        break;
      }
      num = num * 10 + digit;
    }
  }

  if (digits_found || chars_processed > 0) {
    if (overflow) {
      num = (sign == 1) ? LONG_MAX : LONG_MIN;
    } else if (digits_found) {
      num *= sign;
    } else {
      num = 0;
    }

    if (!skip && digits_found) {
      if (modifier == 'h') {
        *va_arg(args, short *) = (short)num;
      } else if (modifier == 'l') {
        *va_arg(args, long *) = num;
      } else {
        *va_arg(args, int *) = (int)num;
      }
      count = 1;
    }
  }

  while (skip && !s21_isspace(*str)) str++;

  *str_ptr = str;
  return count;
}
int s21_specifier_u(va_list args, const char **str_ptr, int skip, int width,
                    int modifier) {
  const char *str = *str_ptr;
  int count = 0;
  unsigned long num = 0;
  int digits_found = 0;
  int overflow = 0;
  int negative = 0;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    if (!digits_found) {
      return -1;
    }
  }

  if (*str == '-' || *str == '+') {
    negative = (*str == '-');
    str++;
    if (width) width--;
  }

  if (width > 0) {
    while (width-- > 0 && s21_isdigit(*str)) {
      int digit = *str++ - '0';
      digits_found = 1;

      if (num > ULONG_MAX / 10 ||
          (num == ULONG_MAX / 10 && digit > (int)(ULONG_MAX % 10))) {
        overflow = 1;
        while ((width == 0 || width-- > 0) && s21_isdigit(*str)) str++;
        break;
      }
      num = num * 10 + digit;
    }
  } else if (width == 0) {
    while (s21_isdigit(*str)) {
      int digit = *str++ - '0';
      digits_found = 1;
      num = num * 10 + digit;
    }
  }

  if (overflow) {
    num = ULONG_MAX;
  } else if (negative) {
    num = (unsigned long)(-(long)num);
  }

  if (!skip && digits_found) {
    if (modifier == 'h') {
      *va_arg(args, unsigned short *) = (unsigned short)(num & USHRT_MAX);
    } else if (modifier == 'l') {
      *va_arg(args, unsigned long *) = num;
    } else {
      *va_arg(args, unsigned int *) = (unsigned int)(num & UINT_MAX);
    }
    count++;
  }

  while (skip && !s21_isspace(*str)) str++;

  *str_ptr = str;
  return count;
}
int s21_specifier_i(va_list args, const char **str_ptr, int skip, int width,
                    int modifier) {
  const char *str = *str_ptr;
  int count = 0;
  long num = 0;
  int base = 10;
  int sign = 1;
  int digits_found = 0;
  int char_proccesed = 0;
  int fl_width = 0;
  int fl_pref = 0;
  int fl_oct = 0;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    return -1;
  }

  if (*str == '-' || *str == '+') {
    sign = (*str == '-') ? -1 : 1;
    str++;
    if (width > 0) width--;
  }

  if (*str == '0') {
    if (width > 0 && width <= 1) {
      fl_width = 1;
    }
    str++;
    if (width > 0) width--;
    if (*str == 'x' || *str == 'X') {
      if (width > 0 && width <= 1) {
        fl_width = 1;
      }
      fl_pref = 1;
      base = 16;
      str++;
      if (width > 0) width--;
    } else {
      base = 8;
      fl_oct = 1;
      fl_pref = 1;
      digits_found = 1;
    }
  }

  if (!fl_width) {
    while (*str && (width == 0 || char_proccesed < width)) {
      int digit = 0;
      if (s21_isdigit(*str) && !fl_oct) {
        digit = *str - '0';
      } else if (base == 16 && s21_isxdigit(*str)) {
        digit = s21_tolower(*str) - 'a' + 10;
      } else if (base == 8 && s21_isoct(*str) && fl_oct) {
        digit = *str - '0';
      } else {
        break;
      }

      if (sign == 1) {
        if (num > LONG_MAX / base ||
            (num == LONG_MAX / base && digit > LONG_MAX % base)) {
          num = LONG_MAX;
          break;
        }
      } else {
        unsigned long abs_max = (unsigned long)LONG_MAX + 1;
        if ((unsigned long)num > abs_max / base ||
            ((unsigned long)num == abs_max / base &&
             (unsigned)digit > abs_max % base)) {
          num = LONG_MIN;
          break;
        }
      }
      char_proccesed++;
      num = num * base + digit;
      digits_found++;
      str++;
    }
  }

  if (fl_pref && num == 0) {
    if (modifier == 'h')
      *va_arg(args, short *) = (short)num;
    else if (modifier == 'l')
      *va_arg(args, long *) = (long)num;
    else
      *va_arg(args, int *) = (int)num;
    count++;
    *str_ptr = str;
    return count;
  }

  num *= sign;
  if (!skip && digits_found > 0) {
    if (modifier == 'h')
      *va_arg(args, short *) = (short)num;
    else if (modifier == 'l')
      *va_arg(args, long *) = (long)num;
    else
      *va_arg(args, int *) = (int)num;
    count++;
  }

  *str_ptr = str;
  return count;
}
int s21_specifier_e_E_f_F_g_G(va_list args, const char **str_ptr, int skip,
                              int width, int modifier) {
  const char *str = *str_ptr;
  int count = 0;
  double sign = 1.0;
  long double num = 0.0;
  int exponent = 0;
  double fraction = 1.0;
  int chars_processed = 0;
  int has_digits = 0;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    return -1;
  }

  if (!skip && (width == 0 || chars_processed < width)) {
    if (s21_strncmp(str, "infinity", 8) == 0 ||
        s21_strncmp(str, "inf", 3) == 0 || s21_strncmp(str, "INF", 3) == 0) {
      if (s21_strncmp(str, "infinity", 8) == 0) {
        str += 8;
        chars_processed += 8;
      } else {
        str += 3;
        chars_processed += 3;
      }
      num = INFINITY;
      has_digits = 1;
    }

    else if (s21_strncmp(str, "nan", 3) == 0 ||
             s21_strncmp(str, "NAN", 3) == 0) {
      str += 3;
      chars_processed += 3;

      if (*str == '(') {
        str++;
        int parentheses = 1;
        while (*str && parentheses > 0) {
          if (*str == '(') parentheses++;
          if (*str == ')') parentheses--;
          str++;
        }
      }
      num = NAN;
      has_digits = 1;
    }
  }

  if ((*str == '-' || *str == '+') && (width == 0 || chars_processed < width)) {
    sign = (*str == '-') ? -1 : 1;
    str++;
    chars_processed++;
  }

  if (skip) {
    while (*str && !s21_isspace(*str)) {
      str++;
    }
  }

  while (s21_isdigit(*str) && (width == 0 || chars_processed < width)) {
    num = num * 10.0 + (*str - '0');
    str++;
    chars_processed++;
    has_digits = 1;
  }

  if (*str == '.' && (width == 0 || chars_processed < width)) {
    str++;
    chars_processed++;
    while (s21_isdigit(*str) && (width == 0 || chars_processed < width)) {
      num = num * 10.0 + (*str - '0');
      fraction *= 10.0;
      str++;
      chars_processed++;
      has_digits = 1;
    }
  }

  if ((*str == 'e' || *str == 'E') && (width == 0 || chars_processed < width)) {
    str++;
    chars_processed++;
    int exp_sign = 1;
    int exp_val = 0;

    if ((*str == '-' || *str == '+') &&
        (width == 0 || chars_processed < width)) {
      exp_sign = (*str == '-') ? -1 : 1;
      str++;
      chars_processed++;
    }

    while (s21_isdigit(*str) && (width == 0 || chars_processed < width)) {
      exp_val = exp_val * 10 + (*str - '0');
      str++;
      chars_processed++;
    }

    exponent = exp_sign * exp_val;
  }

  if (has_digits) {
    num = sign * (num / fraction) * pow(10.0, exponent);
    if (modifier == 'L') {
      *va_arg(args, long double *) = (long double)num;
    } else {
      *va_arg(args, double *) = (double)num;
    }
    count++;
  }

  *str_ptr = str;
  return count;
}

int s21_specifier_o(va_list args, const char **str_ptr, int skip, int width,
                    int modifier) {
  const char *str = *str_ptr;
  int count = 0;

  int chars_processed = 0;
  unsigned long num = 0;
  int digits_found = 0;
  int negative = 0;

  while (s21_isspace(*str)) {
    str++;
  }
  if (*str == '\0') {
    return -1;
  }

  if (*str == '-' || *str == '+') {
    if (*str == '-') negative = 1;
    str++;
    if (width > 0) width--;
  }

  while (*str && (width == 0 || chars_processed < width)) {
    if (s21_isoct(*str)) {
      num = num * 8 + (*str - '0');
      str++;
      chars_processed++;
      digits_found = 1;
    } else {
      break;
    }
  }

  if (digits_found && !skip) {
    unsigned long value = num;

    if (modifier == 'h') {
      if (negative) {
        *va_arg(args, short *) = (short)(-value);
      } else {
        *va_arg(args, unsigned short *) = (unsigned short)value;
      }
    } else if (modifier == 'l') {
      if (negative) {
        *va_arg(args, long *) = (long)(-value);
      } else {
        *va_arg(args, unsigned long *) = value;
      }
    } else {
      if (negative) {
        *va_arg(args, int *) = (int)(-value);
      } else {
        *va_arg(args, int *) = (int)num;
      }
    }
    count++;
  }

  *str_ptr = str;
  return count;
}
int s21_specifier_x_X(va_list args, const char **str_ptr, int skip, int width,
                      int modifier) {
  const char *str = *str_ptr;
  int count = 0;
  int chars_processed = 0;
  unsigned long num = 0;
  int sign = 1;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    return -1;
  }

  if (*str == '-' || *str == '+') {
    sign = (*str == '-') ? -1 : 1;
    str++;
    if (width > 0) width++;
  }

  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
    if (width > 0) width -= 2;
  }

  while (*str && (width == 0 || chars_processed < width)) {
    int digit = 0;
    if (s21_isdigit(*str)) {
      digit = *str - '0';
    } else if (s21_isxdigit(*str)) {
      digit = s21_tolower(*str) - 'a' + 10;
    } else
      break;
    num = num * 16 + digit;
    chars_processed++;
    str++;
  }

  num *= sign;

  if (!skip && chars_processed > 0) {
    if (modifier == 'h') {
      *va_arg(args, unsigned short *) = (unsigned short)num;
    } else if (modifier == 'l') {
      *va_arg(args, unsigned long *) = num;
    } else {
      *va_arg(args, unsigned int *) = (unsigned int)num;
    }
    count++;
  }

  *str_ptr = str;
  return count;
}
int s21_specifier_s(va_list args, const char **str_ptr, int skip, int width) {
  const char *str = *str_ptr;
  int count = 0;
  int char_processed = 0;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    return -1;
  }

  if (!skip) {
    int i;
    char *ptr = va_arg(args, char *);
    for (i = 0; *str != '\0'; i++, str++) {
      if (!s21_isspace(*str) && (width == 0 || char_processed < width)) {
        ptr[i] = *str;
        char_processed++;
      } else
        break;
    }
    ptr[i] = '\0';
    count++;
  } else if (skip) {
    for (; *str != '\0' && !s21_isspace(*str) &&
           (width == 0 || char_processed < width);
         str++) {
      char_processed++;
    }
  }

  *str_ptr = str;
  return count;
}
int s21_specifier_p(va_list args, const char **str_ptr, int skip, int width) {
  const char *str = *str_ptr;
  int count = 0;
  unsigned long num = 0;
  int chars_processed = 0;
  int digits_found = 0;
  int sign = 1;

  while (s21_isspace(*str)) str++;
  if (*str == '\0') {
    return -1;
  }

  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
    digits_found = 1;
    if (width > 0) width -= 2;
  } else if (*str == '0') {
    str += 1;
    if (width > 0) width--;
  }

  while (s21_isxdigit(*str) && (width == 0 || chars_processed < width)) {
    unsigned digit = 0;
    if (s21_isdigit(*str))
      digit = *str - '0';
    else if (s21_isxdigit(*str))
      digit = s21_tolower(*str) - 'a' + 10;

    chars_processed++;
    num = num * 16 + digit;
    str++;
    digits_found = 1;
  }

  num *= sign;

  if (!skip && digits_found) {
    void **ptr = va_arg(args, void **);
    *ptr = (void *)(unsigned long)num;
    count = 1;
  }

  *str_ptr = str;
  return count;
}
void s21_specifier_n(va_list args, const char *start_pos,
                     const char *current_pos) {
  int *ptr = va_arg(args, int *);
  *ptr = (int)(current_pos - start_pos);
}
