gtest: sprite
	g++ -o spriteTests -std=c++11 sprite.o WriteGIF.o test/spriteTests.cpp -L test/gtest/ -I ./ -I test/gtest/include -lgtest -lgtest_main -lpthread `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs` -O2
sprite: sprite.h sprite.cpp ../SpriteCreator/WriteGIF.h
	g++ -c ../SpriteCreator/WriteGIF.cpp sprite.cpp -I ../SpriteCreator/ `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs` -O2
gif: ../SpriteCreator/WriteGIF.cpp
	g++ -c ../SpriteCreator/WriteGIF.cpp -I ../SpriteCreator/
test: gtest
	./spriteTests
import: gifImport.cpp sprite.h sprite.cpp
	g++ ../SpriteCreator/WriteGIF.cpp sprite.o gifImport.cpp -I ../SpriteCreator/ `Magick++-config --cxxflags --cppflags` `Magick++-config --ldflags --libs` -O2 -o gifImport
clean:
	rm spriteTests sprite.o sprite.h.gch WriteGIF.o rainbowTest.gif gifImport