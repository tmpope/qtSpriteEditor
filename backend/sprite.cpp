#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <WriteGIF.h>
#include "sprite.h"
#include <cstring>
#include <stack>
#include <list>
#include <Magick++.h>

Sprite::Sprite(int height, int width)
{
    this->width = width;
    this->height = height;
    this->frameCount = 1;
    int size = this->frameCount * this->height * this->width;
    this->pixels = new struct color[size];
    for(int i = 0; i < size; i++) {
        pixels[i].r = 255;
        pixels[i].g = 255;
        pixels[i].b = 255;
        pixels[i].a = 0;
    }

}

Sprite::Sprite(std::string sspString)
{

    std::vector<int> sprite;
    std::stringstream ss(sspString);
    int i;

    while (ss >> i)
    {
        sprite.push_back(i);

        if (ss.peek() == ' ' || ss.peek() == '\n')
            ss.ignore();
    }
    if (sprite.size() < 3 || sprite.size() != 3 + 4 * sprite[0] * sprite[1] * sprite[2])
    {
        std::cout << "Improper .ssp file" << std::endl;
    }
    this->width = sprite[0];
    this->height = sprite[1];
    this->frameCount = sprite[2];
    int size = this->frameCount * this->height * this->width;
    this->pixels = new struct color[size];
    for(int i = 0; i < size; i++)
    {
        pixels[i].r = sprite[3 + 4 * i + 0];
        pixels[i].g = sprite[3 + 4 * i + 1];
        pixels[i].b = sprite[3 + 4 * i + 2];
        pixels[i].a = sprite[3 + 4 * i + 3];
    }
}

Sprite::Sprite(std::string gifFileName, bool isGif) {
    Magick::InitializeMagick("./demo");

    std::list<Magick::Image> imageList;
    std::vector<Magick::Image> frames;

    /* read all the frames of the animated GIF */
    Magick::readImages( &imageList, gifFileName);

    this->width = imageList.front().columns();
    this->height = imageList.front().rows();
    this->frameCount = imageList.size();
    int size = this->frameCount * this->height * this->width;
    this->pixels = new struct color[size];

    std::list<Magick::Image>::const_iterator listIterator = imageList.begin();
    for (listIterator; listIterator != imageList.end(); ++listIterator)
    {
        frames.push_back(*listIterator);
    }
    for (int frame = 0; frame < frameCount; frame++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                int loc = frame * width * height + y * width + x;
                Magick::PixelPacket* pixel = frames[frame].getPixels(x, y, 1, 1);
                pixels[loc].r = pixel->red;
                pixels[loc].g = pixel->green;
                pixels[loc].b = pixel->blue;
                pixels[loc].a = pixel->opacity;
            }
        }
    }
}


Sprite::~Sprite()
{
    delete[] pixels;
}

struct Sprite::color Sprite::getPixel(int x, int y, int frame)
{
    return pixels[frame * width * height + x + y * width];
}

void Sprite::setPixel(int x, int y, int frame, struct color color)
{
    pixels[frame * width * height + x + y * width] = color;
}

void Sprite::fillPixel(int x, int y, int frame, struct color color)
{
    struct color oldColor = getPixel(x, y, frame);
    if (color == oldColor)
        return;
    setPixel(x, y, frame, color);
    if (x - 1 >= 0 && getPixel(x - 1, y, frame) == oldColor)
    {
        fillPixel(x - 1, y, frame, color);
    }
    if (x + 1 < width && getPixel(x + 1, y, frame) == oldColor)
    {
        fillPixel(x + 1, y, frame, color);
    }
    if (y - 1 >= 0 && getPixel(x, y - 1, frame) == oldColor)
    {
        fillPixel(x, y - 1, frame, color);
    }
    if (y + 1 < height && getPixel(x, y + 1, frame) == oldColor)
    {
        fillPixel(x, y + 1, frame, color);
    }
}

void setGifPixel(unsigned char* rgb, int r, int g, int b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}
/**
 * This function does this.
 * @param image  [this will be changed. Look out!]
 * @param sprite [description]
 * @param frame  [description]
 */
void Sprite::drawImage(unsigned char* image, const int frame)
{
    struct Sprite::color pixel;
    for (int x = 0; x< width; x++)
    {
        for (int y = 0; y< height; y++)
        {
            {
                pixel = getPixel(x, y, frame);
                unsigned char* rgb = image + 3 * (x + y * width);
                setGifPixel(rgb, pixel.r, pixel.g, pixel.b);
            }
        }
    }
}


void Sprite::exportToGif(std::string fileName, int fps)
{
    int delay = 100 / fps;
    gif::GIF* g = gif::newGIF(delay);
    unsigned char rgbImage[width * height * 3];
    for(int i=0; i < frameCount; i++)
    {
        drawImage(rgbImage, i);
        gif::addFrame(g, width, height, rgbImage, delay);
    }
    gif::write(g, fileName.c_str());
    gif::dispose(g);
    g = NULL;
}

std::string Sprite::toString()
{
    struct Sprite::color pixel;
    std::stringstream ss;
    ss << height << ' ' << width << std::endl << frameCount;
    for (int frame = 0; frame < frameCount; frame++)
    {
        for (int y = 0; y < height; y++)
        {
            ss << std::endl;
            for (int x = 0; x < width; x++)
            {
                pixel = getPixel(x, y, frame);
                ss << pixel.toString();
                if (x + 1 < width)
                {
                    ss << " ";
                }
            }
        }
    }
    return ss.str();
}

int Sprite::addFrame()
{
    struct color* temp = pixels;
    int size = ++frameCount * height * width;
    this->pixels = new struct color[size];
    memcpy(pixels, temp, 4 * (frameCount - 1) * height * width);
    for (int i = (frameCount - 1) * height * width; i < size; i++)
    {
        pixels[i].r = 255; //TODO change all to 255
        pixels[i].g = 255;
        pixels[i].b = 255;
        pixels[i].a = 0;  //TODO except this one - 0 (transparent)
    }
    delete[] temp;
    return frameCount;
}

int Sprite::removeFrame(int frame)
{
    struct color* temp = pixels;
    int size = --frameCount * height * width;
    this->pixels = new struct color[size];
    int currentFrame = 0;
    for(int i = 0; i < frameCount + 1; i++)
    {
        if(i != frame) {
            memcpy(pixels + currentFrame++ * width * height, temp + i * width * height, 4 * width * height);
        }
    }
    delete[] temp;
    return frameCount;
}

int Sprite::cloneFrame(int frame)
{
    struct color* temp = pixels;
    int size = ++frameCount * height * width;
    this->pixels = new struct color[size];
    int currentFrame = 0;
    for(int i = 0; i < frameCount - 1; i++)
    {
        memcpy(pixels + currentFrame++ * width * height, temp + i * width * height, 4 * width * height);
        if(i == frame) {
        memcpy(pixels + currentFrame++ * width * height, temp + i * width * height, 4 * width * height);
        }
    }
    delete[] temp;
    return frameCount;
}

void Sprite::save(std::string fileName)
{
    std::cout << "Writing sprite to " << fileName;
    std::ofstream myfile;
    myfile.open (fileName.c_str());
    myfile << this->toString();
    myfile.close();
}

void Sprite::undo() {
    // stack::push/pop

    // {
    //   std::stack<int> mystack;

    //   for (int i=0; i<5; ++i) mystack.push(i);

    //   std::cout << "Popping out elements...";
    //   while (!mystack.empty())
    //   {
    //      std::cout << ' ' << mystack.top();
    //      mystack.pop();
    //   }
    //   std::cout << '\n';

    //   return 0;
    // }
}

void Sprite::redo() {

}
