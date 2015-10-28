#include <stdlib.h>
#include <WriteGIF.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <ios>

void setPixel(unsigned char* rgb, int r, int g, int b)
{
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}


int circles(int frame, int x, int y, const int ImageWidth, const int ImageHeight, const int FrameCount, int color) {
	int ret = 255;
	const int c1R = ImageWidth / 5;
	const int c1X1 = -c1R;
	const int c1X2 = c1R+ImageWidth;
	const int c1Y2 = ImageHeight/3;
	const int c1Y1 = ImageHeight*2/3;
	const int c2R = ImageWidth / 6;
	const int c2Y2 = -c2R;
	const int c2Y1 = c2R+ImageHeight;
	const int c2X2 = ImageWidth/3;
	const int c2X1 = ImageWidth*2/3;
	const int c3R = ImageWidth / 4;
	const int c3X2 = -c3R;
	const int c3X1 = c3R+ImageWidth;
	const int c3Y2 = ImageWidth/5;
	const int c3Y1 = ImageHeight*4/5;
	int f3 = (frame + FrameCount*4/5) % FrameCount;
	int f1 = (frame + FrameCount*2/3) % FrameCount;
	int f2 = (frame + FrameCount*3/2) % FrameCount;
	int c1X = (c1X1 * FrameCount + c1X2 * f1- c1X1 * f1) / FrameCount;
	int c1Y = (c1Y1 * FrameCount + c1Y2 * f1- c1Y1 * f1) / FrameCount;
	int c2X = (c2X1 * FrameCount + c2X2 * f2 - c2X1 * f2) / FrameCount;
	int c2Y = (c2Y1 * FrameCount + c2Y2 * f2 - c2Y1 * f2) / FrameCount;
	int c3X = (c3X1 * FrameCount + c3X2 * f3 - c3X1 * f3) / FrameCount;
	int c3Y = (c3Y1 * FrameCount + c3Y2 * f3 - c3Y1 * f3) / FrameCount;
	if(color == 0) {
		int d1x = (c1X - x), d1y = (c1Y - y);
		if(d1x * d1x + d1y * d1y < c1R * c1R) ret = 200;//setPixel(rgb, 200, 0, 0);
		int d2x = (c2X - x), d2y = (c2Y - y);
		if(d2x * d2x + d2y * d2y < c2R * c2R) ret = 200;//setPixel(rgb, 200, 200, 0);
		int d3x = (c3X - x), d3y = (c3Y - y);
		if(d3x * d3x + d3y * d3y < c3R * c3R) ret = 0;//setPixel(rgb, 0, 100, 200);
	}
	if(color == 1) {
		int d1x = (c1X - x), d1y = (c1Y - y);
		if(d1x * d1x + d1y * d1y < c1R * c1R) ret = 0;//setPixel(rgb, 200, 0, 0);
		int d2x = (c2X - x), d2y = (c2Y - y);
		if(d2x * d2x + d2y * d2y < c2R * c2R) ret = 200;//setPixel(rgb, 200, 200, 0);
		int d3x = (c3X - x), d3y = (c3Y - y);
		if(d3x * d3x + d3y * d3y < c3R * c3R) ret = 100;//setPixel(rgb, 0, 100, 200);
	}
	if(color == 2) {
		int d1x = (c1X - x), d1y = (c1Y - y);
		if(d1x * d1x + d1y * d1y < c1R * c1R) ret = 0;//setPixel(rgb, 200, 0, 0);
		int d2x = (c2X - x), d2y = (c2Y - y);
		if(d2x * d2x + d2y * d2y < c2R * c2R) ret = 0;//setPixel(rgb, 200, 200, 0);
		int d3x = (c3X - x), d3y = (c3Y - y);
		if(d3x * d3x + d3y * d3y < c3R * c3R) ret = 200;//setPixel(rgb, 0, 100, 200);
	}
	return ret;
}

int getRed(int frame, int x, int y, const int ImageWidth, const int ImageHeight, const int FrameCount) {
	return circles(frame, x, y, ImageWidth, ImageHeight, FrameCount, 0);
}

int getGreen(int frame, int x, int y, const int ImageWidth, const int ImageHeight, const int FrameCount) {
	return circles(frame, x, y, ImageWidth, ImageHeight, FrameCount, 1);
}

int getBlue(int frame, int x, int y, const int ImageWidth, const int ImageHeight, const int FrameCount) {
	return circles(frame, x, y, ImageWidth, ImageHeight, FrameCount, 2);
}

void drawImage(unsigned char* image, const int ImageWidth, const int ImageHeight, const int frame, const int FrameCount)
{
	for(int y=0; y<ImageHeight; y++){
		for(int x=0; x<ImageWidth; x++){
			{
				unsigned char* rgb = image + 3 * (ImageWidth * y + x);
				setPixel(rgb, getRed(frame, x, y, ImageWidth, ImageHeight, FrameCount), getGreen(frame, x, y, ImageWidth, ImageHeight, FrameCount), getBlue(frame, x, y, ImageWidth, ImageHeight, FrameCount));
			}
		}
	}
}

void drawImage(unsigned char* image, const std::vector<int> sprite, const int frame)
{
	int pixel = 0;
	for(int y=0; y< sprite[0]; y++){
		for(int x=0; x< sprite[1]; x++){
			{
				pixel = 3 + (frame * sprite[0] * sprite[1] * 4) + 4 * (sprite[1] * y + x);
				unsigned char* rgb = image + 3 * (sprite[1] * y + x);
				setPixel(rgb, sprite[pixel + 0], sprite[pixel + 1], sprite[pixel + 2]);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		std::cout << "Please provide a .ssp file" << std::endl;
		return 1;
	}

    std::string spriteFile = argv[1];

    std::fstream fp;
	std::vector<int> sprite;
	int number;

	fp.open(spriteFile, std::ios::in | std::ios::binary);

	if(fp.is_open()){
	  while(fp >> number){
	     sprite.push_back(number);
	     fp.get();
	  }
	}

	fp.close();

	gif::GIF* g = gif::newGIF(3);
	const int W = sprite[0], H = sprite[1];
	unsigned char rgbImage[W * H * 3];
	const int FrameCount = sprite[2];
	for(int i=0; i<FrameCount; i++){
		// drawImage(rgbImage, W, H, i, FrameCount);
		drawImage(rgbImage, sprite, i);
		gif::addFrame(g, W, H, rgbImage, 0);
	}
	gif::write(g, NULL);
	gif::dispose(g);
	g = NULL;
	return 0;
}
