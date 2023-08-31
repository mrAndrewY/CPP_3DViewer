CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic
LFLAGS = -lstdc++
LDFLAGS = -lgtest -lgtest_main -lpthread
LIB = s21_3dviewer2.a
APP_NAME = s21_3DViewer2
SHRTCT_NAME = s21_3DViewer2.app
MODEL_SOURCES = affins.cc commands.cc multipult.cc model.cc
LEAK_1 = leaks
LEAK_2 = leaks1
DVI_0 = dvi_docker
DVI_1 = dvi
DVI_2 = dvi1
ifeq ($(shell uname -s), Linux)
	LDFLAGS += -lm -lsubunit
	SRC_ICO = 3dv.png
	LEAK_1 = leaks1
	LEAK_2 = leaks
	DVI_1 = dvi1
	DVI_2 = dvi
	SHRTCT_NAME = s21_3DViewer2
else ifeq ($(shell uname -s), Darwin)
	SRC_ICO = 3dv.icns
else
	SRC_ICO = 3dv.ico
endif
INST_SRC = *.cc *.h *.ui $(SRC_ICO) $(APP_NAME).pro QtGifImage
SRC_TEST =  gtests.cc
OBJECTS = *.o

all: install

install:
	mkdir ../build
	cp -r $(INST_SRC) ../build
	cd ../build && qmake $(APP_NAME).pro && make
	cd ../build && ln -s $$PWD/$(SHRTCT_NAME) ~/Desktop/

uninstall:
	rm -rf ~/Desktop/$(SHRTCT_NAME)
	rm -rf ../build

clean:
	rm -f *.o *.a *.gcda *.gcno *.gcov *.out *.html *.info
	rm -f test
	rm -rf $(APP_NAME)_report *.dSYM
	rm -rf ~/Desktop/$(APP_NAME).tar.gz
	rm -f *.pdf valgrind-out.txt
	rm -rf *report

$(DVI_1):
	docker rmi -f school21/valgrind:1.0 && docker build . -t school21/valgrind:1.0 -f Dockerfile && docker run -itd school21/valgrind:1.0
	sleep 1	
	./host_dvi.sh
	open readme.pdf

$(DVI_2): 
	open README.md

$(LIB):
	$(CC) $(CFLAGS) -c $(MODEL_SOURCES) $(LFLAGS)
	ar rc $(LIB) $(OBJECTS)
	ranlib $(LIB)
	rm -f $(OBJECTS)

dist: install
	cd ../ && tar -cvzf ~/Desktop/$(APP_NAME).tar.gz build

tests: clean $(LIB)
	$(CC) $(CFLAGS) $(SRC_TEST) $(LIB) $(LDFLAGS) -o test $(LFLAGS)
	./test
	make clean

format: 
	clang-format --style=Google -n *.cc *.h

$(LEAK_1): clean $(LIB)
	$(CC) $(CFLAGS) $(SRC_TEST) $(LIB) $(LDFLAGS) -o test $(LFLAGS)
	leaks -atExit -- ./test
	make clean

$(LEAK_2): clean $(LIB)
	$(CC) $(CFLAGS) $(SRC_TEST) $(LIB) $(LDFLAGS) -o test $(LFLAGS)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt ./test
	grep "ERROR" valgrind-out.txt
	# make clean

gcov_report: for_report
	lcov -t "$(APP_NAME)" -o $(APP_NAME).info -c -d . --rc lcov_branch_coverage=1
	genhtml -o $(APP_NAME)_report $(APP_NAME).info --rc lcov_branch_coverage=1
	rm -f *.gcda *.gcno *.gcov *.info test
	open $(APP_NAME)_report/index.html

gcov_report1: for_report
	gcov *.gcda
	gcovr
	mkdir $(APP_NAME)_report
	gcovr --html-details $(APP_NAME)_report/index.html
	rm -f *.gcov *.gcda *.gcno test
	open $(APP_NAME)_report/index.html

for_report: clean
	$(CC) $(CFLAGS) -c --coverage $(MODEL_SOURCES) $(LFLAGS)
	$(CC) $(CFLAGS) -c $(SRC_TEST) $(LFLAGS)
	$(CC) $(CFLAGS) $(OBJECTS) --coverage $(LDFLAGS) -o test $(LFLAGS)
	./test

rebuild: clean all
