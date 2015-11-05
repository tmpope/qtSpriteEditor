#include "sprite.h"
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


void printPixel(Sprite& s, int x, int y) 
{
	std::cout << "-----------" << std::endl;
	for (int i = 0; i < s.getFrameCount(); i++) 
	{
		std::cout 
		<< s.getPixel(x, y, i).r 
		<< s.getPixel(x, y, i).g 
		<< s.getPixel(x, y, i).b 
		<< s.getPixel(x, y, i).a 
		<< std::endl;
	}
}

TEST(BasicCases, Instantiate) 
{
	Sprite sprite(10,10);
	EXPECT_EQ(10, sprite.getHeight());
	EXPECT_EQ(10, sprite.getWidth());
	EXPECT_EQ(1, sprite.getFrameCount());
}

TEST(BasicCases, Pointer) 
{
	Sprite* sprite;
	sprite = new Sprite(10,10);
	EXPECT_EQ(10, sprite->getHeight());
	EXPECT_EQ(10, sprite->getWidth());
	EXPECT_EQ(1, sprite->getFrameCount());
	delete sprite;
}

TEST(BasicCases, PointerReallocate) 
{
	Sprite* sprite;
	sprite = new Sprite(10,10);
	EXPECT_EQ(10, sprite->getHeight());
	EXPECT_EQ(10, sprite->getWidth());
	EXPECT_EQ(1, sprite->getFrameCount());
	delete sprite;
	sprite = new Sprite(4, 23436);
	sprite->addFrame();
	EXPECT_EQ(4, sprite->getHeight());
	EXPECT_EQ(23436, sprite->getWidth());
	EXPECT_EQ(2, sprite->getFrameCount());
	delete sprite;
}

TEST(Frames, RemoveEndFrames) 
{
	Sprite s(10, 10);
	EXPECT_EQ(1, s.getFrameCount());
	s.addFrame();
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(2);
	EXPECT_EQ(2, s.getFrameCount());
	s.removeFrame(1);
	EXPECT_EQ(1, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(0, s.getFrameCount());
}

TEST(Frames, RemoveMiddleFrames) 
{
	Sprite s(7, 32);
	EXPECT_EQ(1, s.getFrameCount());
	s.addFrame();
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(1);
	EXPECT_EQ(2, s.getFrameCount());
}

TEST(Frames, RemoveBeginingFrames) 
{
	Sprite s(3, 100);
	EXPECT_EQ(1, s.getFrameCount());
	s.addFrame();
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(2, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(1, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(0, s.getFrameCount());
}

TEST(Frames, RemoveCorrectFrames) 
{
	Sprite s(1, 1);
	s.addFrame();
	s.addFrame();
	s.setPixel(0, 0, 1, 5, 5, 5, 5);
	s.setPixel(0, 0, 2, 55, 55, 55, 55);
	struct Sprite::color defaultColor(255,255,255,0);
	struct Sprite::color frameOneColor(5, 5, 5, 5);
	struct Sprite::color frameTwoColor(55, 55, 55, 55);
	EXPECT_EQ(defaultColor, s.getPixel(0,0,0));
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,1));
	EXPECT_EQ(frameTwoColor, s.getPixel(0,0,2));
	EXPECT_EQ(3, s.getFrameCount());
	s.removeFrame(0);
	EXPECT_EQ(2, s.getFrameCount());
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,0));
	EXPECT_EQ(frameTwoColor, s.getPixel(0,0,1));
	s.addFrame();
	EXPECT_EQ(3, s.getFrameCount());
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,0));
	EXPECT_EQ(frameTwoColor, s.getPixel(0,0,1));
	EXPECT_EQ(defaultColor, s.getPixel(0,0,2));
	s.removeFrame(1);
	EXPECT_EQ(2, s.getFrameCount());
	EXPECT_EQ(frameOneColor, s.getPixel(0,0,0));
	EXPECT_EQ(defaultColor, s.getPixel(0,0,1));
}

TEST(SetPixel, BasicSet) 
{
	Sprite s(5, 5);
	s.addFrame();
	s.addFrame();
	for (int i = 0; i < s.getFrameCount(); i++) 
	{
		for (int j = 0; j < s.getWidth(); j++)
		{
			for (int k = 0; k < s.getHeight(); k++)
			{
				s.setPixel(j, k, i, j, k, i, 0);
			}
		}
	}
	for (int i = 0; i < s.getFrameCount(); i++) 
	{
		for (int j = 0; j < s.getWidth(); j++)
		{
			for (int k = 0; k < s.getHeight(); k++)
			{
				struct Sprite::color check(j, k, i, 0);
				EXPECT_EQ(check, s.getPixel(j, k, i));
			}
		}
	}
}

TEST(Fill, FillBlankFrame) 
{
	Sprite s(3, 3);
	struct Sprite::color defaultColor(255,255,255,0);
	struct Sprite::color newColor(70, 70, 70, 70);
	for (int i = 0; i < s.getWidth(); i++) 
	{
		for (int j = 0; j < s.getHeight(); j++)
		{
			EXPECT_EQ(defaultColor, s.getPixel(i, j, 0));
		}
	}
	s.fillPixel(0, 0, 0, newColor);
	for (int i = 0; i < s.getWidth(); i++) 
	{
		for (int j = 0; j < s.getHeight(); j++)
		{
			EXPECT_EQ(newColor, s.getPixel(i, j, 0));
		}
	}
}

TEST(Export, GifExport) 
{
	FAIL(); //needs to be implemented to test somehow.
}

TEST(Export, ColorToString)
{
	struct Sprite::color c(1, 23, 249, 0);
	EXPECT_EQ("1 23 249 0", c.toString());
}

TEST(Export, ToString)
{
	Sprite s(2, 2);
	s.setPixel(0, 0, 0, 01, 02, 03, 04);
	s.setPixel(1, 0, 0, 21, 22, 23, 24);
	s.setPixel(0, 1, 0, 11, 12, 13, 14);
	s.setPixel(1, 1, 0, 31, 32, 33, 34);
	std::string expected("2 2\n1\n1 2 3 4 21 22 23 24\n11 12 13 14 31 32 33 34");
	EXPECT_EQ(expected, s.toString());
}
