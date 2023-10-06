
all: dir bin/ut_all

bin/ut_all: test/ut_all.cpp test/file_test.h src/file.h test/folder_test.h src/folder.h test/node_test.h src/node.h test/iterator_test.h src/iterator.h src/dfs_iterator.h iterator.o
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o:
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

clean:
	rm -rf bin obj

dir:
	mkdir -p bin obj
