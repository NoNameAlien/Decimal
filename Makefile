CFLAGS = -Wall -Werror -Wextra -lm
CFILES = s21_tools.c s21_convert.c s21_others.c s21_comparisons.c s21_arithmetic.c
#OFILES = $(wildcard *.o)
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
#CTESTS = tests/add.check
#CTESTS = tests.check
TST_FILES=s21_test.c s21_support_test.c

all: clean style s21_decimal.a gcov_report

#convert_test:
#	checkmk clean_mode=1 $(CTESTS) > test_s21_decimal.c	

test: clean s21_decimal.a
	gcc -c $(TST_FILES) -lcheck
	gcc s21_support_test.o s21_test.o s21_decimal.a -o s21_test -lcheck
	./s21_test

gcov_report: clean
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage $(TST_FILES) $(CFILES) -o s21_test `pkg-config --cflags --libs check`
	./s21_test
	rm -rf s21_support_test.g* s21_test.g* 
	lcov -d ./ --capture --output-file s21_test.info
	genhtml s21_test.info --output-directory s21_report
	open ./s21_report/index.html

s21_decimal.a:
	gcc $(CFLAGS) -c $(CFILES)  
	ar -src s21_decimal.a s21_*.o
	ranlib s21_decimal.a

my: clean
	gcc -g $(CFLAGS) $(CFILES) main.c -c -lm
	gcc $(CFLAGS) s21_*.o main.o -o main.exe -lm

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c *.h
	clang-format -n *.c *.h
	rm .clang-format

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf test_s21_decimal.c s21_test
	rm -rf main.exe
	rm -rf *.gcno *.gcda *.info
	rm -rf s21_report

rebuild: clean s21_decimal.a