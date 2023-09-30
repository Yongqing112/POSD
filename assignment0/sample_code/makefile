.PHONY: directories clean stat

all: directories bin/ut_all bin/main

bin/main: src/main.cpp src/hello.h
	g++ -std=c++11 src/main.cpp -o bin/main

bin/ut_all: test/ut_main.cpp test/ut_hello.h src/hello.h
	g++ -std=c++11 test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

directories:
	mkdir -p bin

clean:
	rm -f bin/*

stat:
	wc src/* test/*
