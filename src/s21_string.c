#include "s21_string.h"

#include <stdlib.h>

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *buffer = (const unsigned char *)str;
  unsigned char target = (unsigned char)c;

  void *result = S21_NULL;

  for (s21_size_t i = 0; i < n; ++i) {
    if (buffer[i] == target) {
      result = (void *)(buffer + i);
      break;
    }
  }

  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *byte1 = (const unsigned char *)str1;
  const unsigned char *byte2 = (const unsigned char *)str2;
  int result = 0;

  for (s21_size_t i = 0; i < n; i++) {
    if (byte1[i] != byte2[i]) {
      result = byte1[i] - byte2[i];
      break;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *start = dest;
  while (*dest != '\0') {
    dest++;
  }
  while (n-- > 0 && *src != '\0') {
    *dest++ = *src++;
  }
  *dest = '\0';
  return start;
}

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc(len + 1);
  if (result == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i <= len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      result[i] = str[i] - ('a' - 'A');
    } else {
      result[i] = str[i];
    }
  }
  return result;
}

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    result = (char *)malloc((len + 1) * sizeof(char));

    if (result != S21_NULL) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          result[i] = str[i] + ('a' - 'A');
        } else {
          result[i] = str[i];
        }
      }
    }
  }

  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_position) {
  char *result = S21_NULL;

  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_len = s21_strlen(src);

    if (start_position <= src_len) {
      s21_size_t str_len = s21_strlen(str);
      s21_size_t new_size = src_len + str_len + 1;
      result = (char *)malloc(new_size);

      if (result != S21_NULL) {
        s21_memcpy(result, src, start_position);
        s21_memcpy(result + start_position, str, str_len);
        s21_memcpy(result + start_position + str_len, src + start_position,
                   src_len - start_position + 1);
      }
    }
  }

  return result;
}

static int trimmed_char_flag(char c, const char *trim_chars) {
  int result = 0;

  if (trim_chars) {
    for (const char *ptr = trim_chars; *ptr && !result; ptr++) {
      result = (*ptr == c);
    }
  } else {
    result = (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
              c == '\r');
  }

  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;

  if (src != S21_NULL) {
    const char *start = src;
    const char *end = src;

    while (*end != '\0') end++;
    while (*start != '\0' && trimmed_char_flag(*start, trim_chars)) start++;

    if (start < end) {
      end--;
      while (start <= end && trimmed_char_flag(*end, trim_chars)) end--;
      end++;
    }

    s21_size_t len = (start < end) ? (s21_size_t)(end - start) : 0;
    result = (char *)malloc(len + 1);

    if (result != S21_NULL) {
      if (len > 0) {
        for (s21_size_t i = 0; i < len; i++) {
          result[i] = start[i];
        }
      }
      result[len] = '\0';
    }
  }

  return result;
}

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    while (*str != '\0' && result == S21_NULL) {
      if (*str == c) {
        result = (char *)str;
      }
      str++;
    }
    if (result == S21_NULL && c == '\0') {
      result = (char *)str;
    }
  }

  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;

  if (n != 0) {
    s21_size_t i = 0;
    int continue_comparing = 1;

    while (i < n && continue_comparing) {
      unsigned char u1 = (unsigned char)str1[i];
      unsigned char u2 = (unsigned char)str2[i];

      if (u1 != u2) {
        result = u1 - u2;
        continue_comparing = 0;
      } else if (u1 == '\0') {
        continue_comparing = 0;
      }

      i++;
    }
  }

  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for (; i < n; i++) {
    dest[i] = '\0';
  }

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  int found = 0;

  while (str1[i] && !found) {
    s21_size_t j = 0;
    while (str2[j] && !found) {
      if (str1[i] == str2[j]) {
        found = 1;
      }
      j++;
    }
    if (!found) {
      i++;
    }
  }

  return i;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;

  if (str != S21_NULL) {
    while (str[length] != '\0') {
      length++;
    }
  }

  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    int found = 0;

    while (*str1 != '\0' && !found) {
      const char *c = str2;
      while (*c != '\0' && !found) {
        if (*str1 == *c) {
          result = (char *)str1;
          found = 1;
        }
        c++;
      }
      if (!found) {
        str1++;
      }
    }
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL) return S21_NULL;

  const char *last_occurrence = S21_NULL;
  const char *current = str;

  while (1) {
    if (*current == (char)c) {
      last_occurrence = current;
    }
    if (*current == '\0') {
      break;
    }
    current++;
  }

  return (char *)last_occurrence;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (haystack != S21_NULL && needle != S21_NULL) {
    if (*needle == '\0') {
      result = (char *)haystack;
    } else {
      s21_size_t n_len = s21_strlen(needle);
      int found = 0;
      s21_size_t i = 0;

      while (haystack[i] != '\0' && !found) {
        if (haystack[i + n_len - 1] == '\0' && n_len > 1) {
          break;
        }

        s21_size_t j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
          j++;
        }

        if (j == n_len) {
          result = (char *)(haystack + i);
          found = 1;
        }

        if (!found) {
          i++;
        }
      }
    }
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last_token = S21_NULL;
  char *result = S21_NULL;
  if (str != S21_NULL) {
    last_token = str;
  } else if (last_token == S21_NULL) {
    return result;
  }
  str = last_token;
  int found_start = 0;
  while (*str && !found_start) {
    const char *d = delim;
    int is_delim = 0;
    while (*d && !is_delim) {
      if (*str == *d) {
        is_delim = 1;
      }
      d++;
    }
    if (!is_delim) {
      found_start = 1;
    } else {
      str++;
    }
  }
  if (*str) {
    char *token_start = str;
    int found_end = 0;
    while (*str && !found_end) {
      const char *d = delim;
      int is_delim = 0;
      while (*d && !is_delim) {
        if (*str == *d) {
          *str = '\0';
          last_token = str + 1;
          is_delim = 1;
          found_end = 1;
        }
        d++;
      }
      if (!found_end) {
        str++;
      }
    }
    if (!found_end) {
      last_token = S21_NULL;
    }
    result = token_start;
  } else {
    last_token = S21_NULL;
  }
  return result;
}
