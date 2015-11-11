#include <iostream>
#include "sprite.h"

int main(int argc,char **argv)
{
    if (argc < 2)
    {
    	std::cout << "Please provide a .gif file" << std::endl;
    }
    if (argc < 3)
    {
    	std::cout << "Please provide a file name" << std::endl;
    }

    Sprite sprite(argv[1], true);
    sprite.save(argv[2]);

    return 0;
}