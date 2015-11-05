all:
	g++ -o spriteTests -std=c++11 sprite.o spriteTests.cpp -L gtest/ -I gtest/include -I .. -lgtest -lgtest_main -lpthread
test: all
	./spriteTests