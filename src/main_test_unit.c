#include "main_test_unit.h"

int main(void) {
  setenv("CK_FORK", "no", 1);

  Suite *suite1 = string_suite();
  Suite *suite2 = s21_sprintf_suite();
  Suite *suite3 = s21_sscanf_suite();

  SRunner *sr = srunner_create(suite1);
  srunner_add_suite(sr, suite2);
  srunner_add_suite(sr, suite3);

  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  printf("\nTOTAL: %d failed\n", failed);
  return (failed == 0) ? 0 : 1;
}