#ifndef TRIE_H
#define TRIE_H


#include <string>
#include <inttypes.h>
#include <sstream>


class Sprite
{
public: //because color needs to be defined before we use it, but needs to be public
	struct color
	{
		color() : r(255), g(255), b(255), a(0) {}
		color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {}
		uint8_t r;
		uint8_t g; 
		uint8_t b; 
		uint8_t a;
		inline bool operator==(const color& other) const
		{
	       return (other.r == r && other.g == g && other.b == b && other.a == a);
	    }
	    inline std::string toString()
	    {
			std::stringstream ss;
			ss << (int) r << ' ' << (int) g << ' ' << (int) b << ' ' << (int) a;
			return ss.str();
	    }
	};
private:
	int width;
	int height;
	int frameCount;
	struct color* pixels;
	void drawImage(unsigned char* image, const int frame);

	Sprite(const Sprite& other);	//copy constructor
	Sprite& operator=(const Sprite& other);

public:
	/**
	 * Pixels each default to white transparent until set otherwise.
	 */
	Sprite(int height, int width);
	Sprite(std::string sspString);
	~Sprite();
	int getHeight() const 
	{
		return this->height;
	}
	int getWidth() const
	{
		return this->width;
	}
	int getFrameCount() const 
	{
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
	void setPixel(int x, int y, int frame, struct color color);
	void setPixel(int x, int y, int frame, int r, int g, int b, int a)
	{
		struct color color(r, g, b, a);
		setPixel(x, y, frame, color);
	}
	/**
	 * For paint bucket. Does not check input. Check your own input.
	 * @param x      [description]
	 * @param y      [description]
	 * @param pixels should have four values, one for each RGBA
	 */
	void fillPixel(int x, int y, int frame, struct color color);
	// void fillRecursive(int x, int y, int frame, struct color color);
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
	/**
	 * Returns the string that needs to be written to a .ssp file
	 * @return [description]
	 */
	std::string toString();
};

#endif