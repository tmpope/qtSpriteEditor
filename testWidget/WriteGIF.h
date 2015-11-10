#pragma once

namespace gif
{
	struct GIF;
	GIF* newGIF(int delay);
	void dispose(GIF* gif);
	/**
	 * [addFrame description]
	 * @param gif      [description]
	 * @param W        [description]
	 * @param H        [description]
	 * @param rgbImage Array of char, storing r, g, and b values for each pixel
	 * @param delay    in hundredths of a second between frames
	 */
	void addFrame(GIF* gif, int W, int H, unsigned char* rgbImage, int delay);
	void write(GIF* gif, const char* filename);
}
