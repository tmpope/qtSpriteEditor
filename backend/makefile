gtest: sprite
	g++ -o spriteTests -std=c++11 sprite.o WriteGIF.o test/spriteTests.cpp -L test/gtest/ -I ./ -I test/gtest/include -lgtest -lgtest_main -lpthread
sprite: sprite.h sprite.cpp ../WriteAnimatedGIF/WriteGIF.h
	g++ -c sprite.h ../WriteAnimatedGIF/WriteGIF.cpp sprite.cpp -I ../WriteAnimatedGIF/
gif: ../WriteAnimatedGIF/WriteGIF.cpp
	g++ -c ../WriteAnimatedGIF/WriteGIF.cpp -I ../WriteAnimatedGIF/
test: gtest
	./spriteTests
clean:
	rm spriteTests sprite.o sprite.h.gch WriteGIF.o
