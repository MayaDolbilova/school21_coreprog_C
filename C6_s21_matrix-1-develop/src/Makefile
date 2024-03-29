cc = gcc -g -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS =  -lcheck -pthread -lrt -lm 
else
	CHECK_FLAGS = -lcheck
endif

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: s21_matrix.a 

s21_matrix.a:
	$(cc) -c *.c
	ar rc libs21_matrix.a *.o
	rm -rf *.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a

test: s21_matrix.a
	$(cc) s21_matrix.a tests/*.c $(CHECK_FLAGS) -o s21_test -L. -ls21_matrix
	./s21_test

gcov_report: s21_matrix.a
	$(cc) $(GCOVFLAGS) tests/*.c *.c $(CHECK_FLAGS) -o s21_test -L. -ls21_matrix
	./s21_test
	gcov testc/*.c
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda 
	$(OPEN_CMD) ./report/index.html

clang:
	clang-format -style=Google -n *.c *.h tests/*.c

clang-fix:
	clang-format -style=Google -i *.c *.h tests/*.c


leaks: test
	CK_FORK=no leaks --atExit -- ./s21_test

brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

lcov:
ifeq ($(OS),Linux)
	sudo apt install lcov
endif
ifeq ($(OS),Darwin)
	brew install lcov
endif

test_val:
	$(cc) *.c tests/*.c -o run $(CHECK_FLAGS) -lgcov --coverage
	sh valgrind.sh ./run

valgrind: s21_matrix.a
	$(cc) s21_matrix.a tests/*.c -lpthread -lcheck -pthread -lrt -lm -o s21_test -L. -ls21_matrix
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./s21_test

clean:
	rm -rf *.o *.gcno *.gcda *.a *.info report .clang-format s21_test *.out *.dSYM *.gch run *.txt

.PHONY:  all lcov test gcov_report
