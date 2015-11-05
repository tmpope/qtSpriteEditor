gtest: sprite
	g++ -o spriteTests -std=c++11 sprite.o test/spriteTests.cpp -L test/gtest/ -I ./ -I test/gtest/include -lgtest -lgtest_main -lpthread
clean:
	rm spriteTests sprite.o sprite.h.gch
sprite: sprite.h sprite.cpp
	g++ -c sprite.h sprite.cpp -I ../WriteAnimatedGIF/
test: gtest
	./spriteTests
