CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g
COVFLAGS = --coverage


TARGET = main_test_unit
LIB = s21_string.a
SRC = s21_string.c s21_strerror.c s21_sprintf.c s21_sscanf.c 
TEST_SRC = main_test_unit.c main_test_unit.h test_s21_string.c test_s21_sprintf.c test_s21_sscanf.c 
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)
DEPS = s21_string.h s21_sprintf.h s21_sscanf.h s21_strerror_data.h
LDFLAGS = -lcheck -lm -lpthread -lrt -lsubunit


all: $(LIB) $(TARGET)


$(LIB): $(OBJ)
	ar rcs $@ $^


$(TARGET): $(TEST_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


test: clean all
	./$(TARGET)


gcov_report: clean
	$(MAKE) CFLAGS="$(CFLAGS) $(COVFLAGS)" all
	./$(TARGET)
	gcovr -r . --exclude="test_s21.*" --html --html-details -o coverage.html


clean:
	rm -f $(TARGET) *.o *.gcno *.gcda *.gcov $(LIB) coverage*.html coverage*.css 


re: clean all


style:
	clang-format -style=Google -n *.c *.h 
	clang-format -style=Google -i *.c *.h

.PHONY: all clean re test gcov_report style