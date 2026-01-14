#include "s21_strerror_data.h"
#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char buffer[MAX_ERROR_MESSAGE];
  if (errnum >= 0 && errnum < (int)ERRLIST_SIZE) {
    return (char *)ERRLIST[errnum];
  } else {
    s21_sprintf(buffer, "Unknown error %d", errnum);
    return buffer;
  }
}