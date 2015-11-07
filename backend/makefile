gtest: sprite
	g++ -o spriteTests -std=c++11 sprite.o WriteGIF.o test/spriteTests.cpp -L test/gtest/ -I ./ -I test/gtest/include -lgtest -lgtest_main -lpthread
sprite: sprite.h sprite.cpp ../SpriteCreator/WriteGIF.h
	g++ -c ../SpriteCreator/WriteGIF.cpp sprite.cpp -I ../SpriteCreator/
gif: ../SpriteCreator/WriteGIF.cpp
	g++ -c ../SpriteCreator/WriteGIF.cpp -I ../SpriteCreator/
test: gtest
	./spriteTests
clean:
	rm spriteTests sprite.o sprite.h.gch WriteGIF.o rainbowTest.gif
