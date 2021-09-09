# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR_A = ${HOME}/src/googletest-release-1.8.0/googletest
GOOGLE_TEST_LIB = ${HOME}/lib/gtest/libgtest.a
GOOGLE_TEST_INCLUDE = ${HOME}/src/googletest-release-1.8.0/googletest/include/

GTEST_DOWNLOAD = ${HOME}/src/googletest-release-1.8.0/


all: run


Hashtable: Hashtable.c Hashtable.h LinkedList.c LinkedList.h FileProcessor.c FileProcessor.h main.c
	gcc -g Hashtable.c LinkedList.c FileProcessor.c main.c -o main 

run: Hashtable
	./main

### This builds the hashtable library. Change the filenames accordingly. 
Hashtable.o: Hashtable.c Hashtable.h LinkedList.o
	gcc -c -Wall -g Hashtable.c -o Hashtable.o

## Builds the LinkedList library, if you're using it. 
LinkedList.o: LinkedList.c LinkedList.h
	gcc -c -Wall -g LinkedList.c -o LinkedList.o


## Compiles your hashtable tests.
test_hashtable.o : test_hashtable.cc
	g++ -c -Wall -I $(GOOGLE_TEST_INCLUDE) test_hashtable.cc -g\
		-o test_hashtable.o

## Puts it all together. 
test_suite: $(GOOGLE_TEST_LIB) test_hashtable.o Hashtable.o LinkedList.o
	g++ -o test_suite test_hashtable.o Hashtable.o LinkedList.o \
		 -L${HOME}/lib/gtest -lgtest -lpthread
	@echo -e "\033[38;5;198m===================================="
	@echo Run tests by running ./test_suite
	@echo -e "====================================\033[0m"

clean: 
	rm -rf *~ main
