#ifndef TRIE_H
#define TRIE_H


#include <array>
#include <vector>


class Sprite
{
private:
	int width;
	int height;
	int frameCount;
	unsigned char* rgbVals;

public:
	Sprite(int height, int width);
	int getHeight();
	int getWidth();
	int getFrameCount();
	/**
	 * Assumes x and y are in height. Do you want me to return something other than the characters?
	 * @param  x [description]
	 * @param  y [description]
	 * @return   [description]
	 */
	unsigned char* getRGB(int x, int y);
	/**
	 * Does not check input. Check your own input.  Use this for erase as well.
	 * @param x      [description]
	 * @param y      [description]
	 * @param pixels should have four values, one for each RGBA
	 */
	void setPixel(int x, int y, char* pixels);
	/**
	 * For paint bucket. Does not check input. Check your own input.
	 * @param x      [description]
	 * @param y      [description]
	 * @param pixels should have four values, one for each RGBA
	 */
	void fillPixel(int x, int y, char* pixels);
	void exportToGif(std::string fileName);
};

#endif