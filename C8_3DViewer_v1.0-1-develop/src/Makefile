CC 			= gcc
CFLAGS 		= -std=c11 -Wall -Werror -Wextra
TEST_LIBS 	= -lm $(shell pkg-config --cflags --libs check)
BACK_P 		= back_end/
SOURCES 	= $(wildcard back_end/*.c)
OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
PROJECT		= s21_3dviewer
STATIC_LIB	= vue3d.a
COL_CYAN	=| awk '{ print "\033[1;35m" $$0"\033[0m"}'

Name = vue3d.app
ifeq ($(shell uname -s), Linux)
	LFLAGS = -lm -lpthread -lsubunit
	Name = vue3d
endif


all: unzip install execute

unzip:
	unzip objects.zip

install: build
	mkdir -vp install
	@cp -rv build/$(Name) install$(COL_CYAN)
	echo "Starting the application"$(COL_CYAN)

build:
	mkdir -vp build
	cd build && qmake6 ../vue3d/vue3d.pro
	cd build && $(MAKE)

uninstall: clean
	rm -rf vue3d/vue3d.pro.user
	rm -rf build
	rm -rf install

execute:
	cd build && open ./$(Name)

gcov_flag:
	$(eval CFLAGS += --coverage)

debug_flag:
	$(eval CFLAGS += -g)

dist: build
	@tar --totals -cvf build.tar build/$(Name)$(COL_CYAN)

dvi:
	rm -rf docs
ifeq ($(shell uname -s), Darwin)
	brew install doxygen
endif
	doxygen
	cp dolphin.jpg docs/html
	cp dolphin.jpg docs/latex
	open docs/html/index.html

gcov_report: clean gcov_flag test
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf $(BACK_P)*.gcno $(BACK_P)*.gcda $(BACK_P)*.gcov *.gcno *.gcda *.gcov
	open gcov/index.html

$(STATIC_LIB): clean $(OBJECTS)
	ar -rcs $(STATIC_LIB) $(OBJECTS)
	ranlib $(STATIC_LIB)
	rm -f $(BACK_P)*.o


test: clean debug_flag $(STATIC_LIB)
	$(CC) $(CFLAGS) tests/*.c -o test $(STATIC_LIB) $(TEST_LIBS)
	./test

debug: debug_flag test

valgrind:
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i back_end/*.c
	clang-format -i includes/*.h
	clang-format -i tests/*.c 
	clang-format -i tests/*.h
	clang-format -i vue3d/*.cpp 
	clang-format -i vue3d/*.h 

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n back_end/*.c 
	clang-format -n includes/*.h
	clang-format -n tests/*.c 
	clang-format -n tests/*.h
	clang-format -n vue3d/*.cpp 
	clang-format -n vue3d/*.h


clean:
	rm -rf docs test gcov
	rm -rf $(BACK_P)*.o *.a *.gcda *.gcno *.gch *.pdf *.tar rep.info test.info test.dSYM coverage.info
	rm -rf ./build*
	rm -rf ./install*
	rm -rf ./back_end/*.gcda

.PHONY: test all install build dvi clean gcov_report
