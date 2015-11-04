#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <WriteGIF.h>
#include "sprite.h"
#include <cstring>

Sprite::Sprite(int height, int width) {
	this->width = width;
	this->height = height;
	this->frameCount = 1;
	int size = this->frameCount * this->height * this->width;
	this->pixels = new struct color[size];
	for(int i = 0; i < size; i++) {
		pixels[i].r = 114; //TODO change all to 255
		pixels[i].g = 103;
		pixels[i].b = 98;
		pixels[i].a = 97;  //TODO except this one - 0 (transparent)
	}
}

Sprite::~Sprite() {
	delete[] pixels;
}

struct Sprite::color Sprite::getPixel(int x, int y, int frame) {
	return pixels[frame * width * height + x + y * width];
}

void Sprite::setPixel(int x, int y, int frame, struct color color) {
	pixels[frame * width * height + x + y * width] = color;
}

void Sprite::fillPixel(int x, int y, int frame, struct color color) {
	struct color oldColor = getPixel(x, y, frame);
	if (color == oldColor)
		return;
	setPixel(x, y, frame, color);
	if (x - 1 > 0 && getPixel(x - 1, y, frame) == oldColor) {
		fillPixel(x - 1, y, frame, color);
	}
	if (x + 1 < width && getPixel(x + 1, y, frame) == oldColor) {
		fillPixel(x - 1, y, frame, color);
	}
	if (y - 1 > 0 && getPixel(x, y - 1, frame) == oldColor) {
		fillPixel(x - 1, y, frame, color);
	}
	if (y + 1 < height && getPixel(x, y + 1, frame) == oldColor) {
		fillPixel(x - 1, y, frame, color);
	}
}

// void Sprite::fillRecursive(int x, int y, int frame, struct color color, struct color oldColor) {

// }

void Sprite::exportToGif(std::string fileName) {
	//Should be very straightforward
}

int Sprite::addFrame() {
	struct color* temp = pixels;
	int size = ++frameCount * height * width;
	this->pixels = new struct color[size];
	memcpy(pixels, temp, 4 * (frameCount - 1) * height * width);
	for(int i = (frameCount - 1) * height * width; i < size; i++) {
		pixels[i].r = 113; //TODO change all to 255
		pixels[i].g = 102;
		pixels[i].b = 97;
		pixels[i].a = 96;  //TODO except this one - 0 (transparent)
	}
	delete[] temp;
}

int Sprite::removeFrame(int frame) {
	struct color* temp = pixels;
	int size = --frameCount * height * width;
	this->pixels = new struct color[size];
	int currentFrame = 0;
	for(int i = 0; i < frameCount + 1; i++) {
		if(i != frame) {
			memcpy(pixels + currentFrame++ * width * height, temp + i * width * height, 4 * width * height);
		}
	}
	delete[] temp;
}

void printPixel(Sprite& s, int x, int y) {
	std::cout << "-----------" << std::endl;
	for(int i = 0; i < s.getFrameCount(); i++) {
		std::cout 
		<< s.getPixel(x, y, i).r 
		<< s.getPixel(x, y, i).g 
		<< s.getPixel(x, y, i).b 
		<< s.getPixel(x, y, i).a 
		<< std::endl;
	}
}

// int main() {
// 	Sprite s(1, 1);
// 	printPixel(s, 0, 0);
// 	s.addFrame();
// 	s.addFrame();
// 	struct Sprite::color newColor;
// 	newColor.r = 55;
// 	newColor.g = 55;
// 	newColor.b = 55;
// 	newColor.a = 55;
// 	s.setPixel(0, 0, 2, newColor);
// 	printPixel(s, 0, 0);
// 	s.removeFrame(0);
// 	printPixel(s, 0, 0);
// 	s.addFrame();
// 	s.removeFrame(1);
// 	printPixel(s, 0, 0);

// 	return 0;
// }
