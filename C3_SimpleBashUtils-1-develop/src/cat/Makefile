CC=gcc 
CFLAGS=-std=c11 -Wall -Wextra #-Werror
s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clean:
	rm -rf s21_cat s21_cat.dSYM *.o *.out

rebuild: clean s21_cat

leak: s21_cat
	leaks --atExit -- ./s21_cat -e int s21_cat.c -benst test_file/all_flag_tests/*

check: s21_cat
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ./../../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -f CPPLINT.cfg

valgrind_check:
	sh ../../materials/build/run.sh