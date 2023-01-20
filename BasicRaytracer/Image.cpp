#include "image.h"

#include <fstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include <iostream>

Image::Image(int width, int height)
	: width(width), height(height)
{
	data = new float[width * height];
	//data = std::vector<std::vector<float>>(height, std::vector<float>(width, 0));
}

Image::~Image()
{
	delete[] data;
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

float* Image::getPixel(int x, int y)
{
	return data + (x + y * width);
}

void Image::saveImage(std::string filename) const
{
	typedef unsigned char uchar;
	uchar* imgData = new uchar[width * height];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			imgData[x + y * width] = data[x + y * width] == 1 ? 255 : 0;
			//std::cout << data[x + y * width];
		}
		//std::cout << '\n';
	}

	std::cout << "Writing image to " << filename << '\n';

	stbi_write_bmp(filename.c_str(), width, height, 1, imgData);

	delete[] imgData;
}


