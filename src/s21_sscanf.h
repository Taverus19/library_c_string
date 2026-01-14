#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>

int s21_isspace(int c);
int s21_isdigit(int c);
int s21_isxdigit(int c);
int s21_tolower(int c);
int s21_isoct(int c);
void search_modifier(const char **format, int *skip, int *modifier, int *width);
int check_initial_conditions(const char *str, const char *format);
void handle_spaces(const char **format, const char **str);
int handle_regular_char(const char **format, const char **str);
int process_specifier(const char **format, const char **str, va_list args,
                      int *count, const char *str_start);
int s21_specifier_c(va_list args, const char **str_ptr, int skip, int width,
                    int is_long);
int s21_specifier_d(va_list args, const char **str_ptr, int skip, int width,
                    int modifier);
int s21_specifier_u(va_list args, const char **str_ptr, int skip, int width,
                    int modifier);
int s21_specifier_i(va_list args, const char **str_ptr, int skip, int width,
                    int modifier);
int s21_specifier_e_E_f_F_g_G(va_list args, const char **str_ptr, int skip,
                              int width, int modifier);
int s21_specifier_o(va_list args, const char **str_ptr, int skip, int width,
                    int modifier);
int s21_specifier_x_X(va_list args, const char **str_ptr, int skip, int width,
                      int modifier);
int s21_specifier_s(va_list args, const char **str_ptr, int skip, int width);
int s21_specifier_p(va_list args, const char **str_ptr, int skip, int width);
void s21_specifier_n(va_list args, const char *start_pos,
                     const char *current_pos);
int s21_sscanf(const char *str, const char *format, ...);
#endif