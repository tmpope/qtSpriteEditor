gtest: sprite
	g++ -o spriteTests -std=c++11 sprite.o WriteGIF.o test/spriteTests.cpp -L test/gtest/ -I ./ -I test/gtest/include -lgtest -lgtest_main -lpthread
sprite: sprite.h sprite.cpp ../SpriteCreator/WriteGIF.h
	g++ -c ../SpriteCreator/WriteGIF.cpp sprite.cpp -I ../SpriteCreator/ `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs` -O2
gif: ../SpriteCreator/WriteGIF.cpp
	g++ -c ../SpriteCreator/WriteGIF.cpp -I ../SpriteCreator/
test: gtest
	./spriteTests
clean:
	rm spriteTests sprite.o sprite.h.gch WriteGIF.o rainbowTest.gif
magick:
	g++ `Magick++-config --cxxflags --cppflags` -O2 -o demo sprite.cpp   `Magick++-config --ldflags --libs` -I ../SpriteCreator/ -c
