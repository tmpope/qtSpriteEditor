gtest: sprite
	g++ -o spriteTests -std=c++11 sprite.o test/spriteTests.cpp -L test/gtest/ -I ./ -I test/gtest/include -lgtest -lgtest_main -lpthread
all:
	g++ -o sprite sprite.h sprite.cpp -I ../WriteAnimatedGIF/
clean:
	rm sprite
sprite: sprite.h sprite.cpp
	g++ -c sprite.h sprite.cpp -I ../WriteAnimatedGIF/
test: all
	./sprite
