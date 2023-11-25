CC=gcc -std=c11 -Wall -Werror -Wextra -g -pedantic
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
OS = $(shell uname)
ifeq ($(OS), Linux)
#-lsubunit
	F_LIB_CHECK=-lpthread -lcheck -pthread -lrt -lm
else
	F_LIB_CHECK=-lcheck -lm -lpthread
endif

all: clean install dvi dist clean

rebuild: clean all

install: uninstall dvi
	mkdir build
	cp -rf SmartCalc/* build
	cd build && qmake SmartCalc.pro
	make -C build
	cd build && make clean
	open ./build/SmartCalc.app/Contents/MacOS/SmartCalc

uninstall:
	rm -rf build*
	make clean

dist:
	tar -cvf build/calculator.tar build
	gzip build/calculator.tar
	mv build/calculator.tar.gz ./
dvi:
	open readme.txt

test:
	$(CC) $(GCOVFLAGS) *.c -o s21_test $(F_LIB_CHECK) -lgcov --coverage
	./s21_test

gcov_report: test
	lcov -t "test" -o report.info -c -d . 
	genhtml -o gcov_report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index.html

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c 
	clang-format -i *.h 
	clang-format -i SmartCalc/*.cpp 
	clang-format -i SmartCalc/*.h 

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c 
	clang-format -n *.h 
	clang-format -n SmartCalc/*.cpp 
	clang-format -n SmartCalc/*.h 

leaks:   test
	CK_FORK=no leaks --atExit -- ./s21_test

clean:
	@rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        s21_test \
        vtests_run \
		run \
		*.gz \


test_val:
	$(CC) *.c -o run $(F_LIB_CHECK) -lgcov --coverage
	sh valgrind.sh ./run

