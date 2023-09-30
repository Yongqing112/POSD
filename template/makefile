
all: bin/ut_all

bin/ut_all: test/ut_all.cpp #u_test is the target, test/ut.cpp is the depended file
	g++ -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread

clean:
	rm -rf bin/ut_all

