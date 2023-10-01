
all: bin/ut_all

bin/ut_all: test/ut_all.cpp test/file_test.h src/file.h src/node.h #u_test is the target, test/ut.cpp is the depended file
	g++ -Wfatal-errors -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

clean:
	rm -rf bin/ut_all

