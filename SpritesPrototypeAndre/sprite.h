#ifndef TRIE_H
#define TRIE_H


#include <string>
#include <inttypes.h>


class Sprite
{
private:
	struct color
	{
		color() : r(255), g(255), b(255), a(0) {}
		uint8_t r;
		uint8_t g; 
		uint8_t b; 
		uint8_t a;
	};
	int width;
	int height;
	int frameCount;
	struct color* pixels;

	Sprite(const Sprite& other);	//copy constructor
	Sprite& operator=(const Sprite& other);

public:
	/**
	 * Pixels each default to white transparent until set otherwise.
	 */
	Sprite(int height, int width);
	~Sprite();
	int getHeight() {
		return this->height;
	}
	int getWidth() {
		return this->width;
	}
	int getFrameCount() {
		return this->frameCount;
	}
	/**
	 * Assumes x and y are in height. Do you want me to return something other than the characters?
	 * @param  x Columns in from left
	 * @param  y Rows down from top
	 * @return   [description]
	 */
	struct color getPixel(int x, int y, int frame);
	/**
	 * Does not check input. Check your own input.  Use this for erase as well.
	 * @param x      [description]
	 * @param y      [description]
	 * @param pixels should have four values, one for each RGBA
	 */
	void setPixel(int x, int y, struct color color);
	/**
	 * For paint bucket. Does not check input. Check your own input.
	 * @param x      [description]
	 * @param y      [description]
	 * @param pixels should have four values, one for each RGBA
	 */
	void fillPixel(int x, int y, char* pixels);
	void exportToGif(std::string fileName);
	/**
	 * Adds a new frame to the sprite
	 * @return The number of frames after the new frame has been added
	 */
	int addFrame();
	/**
	 * Removes the specified frame from the sprite
	 * @param  frame the number (0 indexed) of the frame to remove
	 *               assumes it is in bound, DOES NOT ERROR CHECK
	 * @return The number of frames after the new frame has been added
	 */
	int removeFrame(int frame);
};

#endif