
all: bin/ut_all

bin/ut_all: test/ut_all.cpp test/file_test.h src/file.h test/folder_test.h src/folder.h src/node.h src/iterator.h iterator.o
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o:
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

clean:
	rm -rf bin/ut_all

