
all: bin/ut_all

bin/ut_all: test/ut_all.cpp test/file_test.h src/file.h test/folder_test.h src/folder.h src/node.h src/iterator.h #u_test is the target, test/ut.cpp is the depended file
	g++ -std=c++11 test/ut_all.cpp obj/folder_iterator.o -o bin/ut_all -lgtest -lpthread
	
clean:
	rm -rf bin/ut_all

