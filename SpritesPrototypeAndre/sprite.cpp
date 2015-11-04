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

Sprite::Sprite(int height, int width){
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

Sprite::~Sprite(){
	delete[] pixels;
}

struct Sprite::color Sprite::getPixel(int x, int y, int frame){
	return pixels[frame * width * height + x + y * width];
}

void Sprite::setPixel(int x, int y, struct color color) {
	pixels[x + y * width] = color;
}

void Sprite::fillPixel(int x, int y, char* pixels){

}

void Sprite::exportToGif(std::string fileName){

}

int Sprite::addFrame(){
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

int Sprite::removeFrame(int frame){
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

int main() {
	Sprite s(1, 1);
	for(int i = 0; i < s.getFrameCount(); i++) {
		std::cout 
		<< s.getPixel(0, 0, i).r 
		<< s.getPixel(0, 0, i).g 
		<< s.getPixel(0, 0, i).b 
		<< s.getPixel(0, 0, i).a 
		<< std::endl;
	}
	s.addFrame();
	for(int i = 0; i < s.getFrameCount(); i++) {
		std::cout 
		<< s.getPixel(0, 0, i).r 
		<< s.getPixel(0, 0, i).g 
		<< s.getPixel(0, 0, i).b 
		<< s.getPixel(0, 0, i).a 
		<< std::endl;
	}
	s.removeFrame(0);
	for(int i = 0; i < s.getFrameCount(); i++) {
		std::cout 
		<< s.getPixel(0, 0, i).r 
		<< s.getPixel(0, 0, i).g 
		<< s.getPixel(0, 0, i).b 
		<< s.getPixel(0, 0, i).a 
		<< std::endl;
	}

	return 0;
}