#include "image.h"

#include <fstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include <iostream>

Image::Image(int width, int height)
	: width(width), height(height)
{
	data = new Color[width * height];
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

Color* Image::getPixel(int x, int y)
{
	return data + (x + y * width);
}

void Image::saveImage(std::string filename, float exposure, float gamma) const
{
	typedef unsigned char uchar;
	uchar* imgData = new uchar[4*width * height];

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Color curColor = data[x + y * width];
			curColor.applyGammaCorrection(exposure, gamma);
			curColor.clamp();

			imgData[4 * (x + y * width) + 3] = 255;
			imgData[4 * (x + y * width) + 2] =
				(uchar)(curColor.r * 255.0f);
			imgData[4 * (x + y * width) + 1] =
				(uchar)(curColor.g * 255.0f);
			imgData[4 * (x + y * width) + 0] =
				(uchar)(curColor.b * 255.0f);

			//std::cout << curColor.r;
		}
		//std::cout << '\n';
	}

	std::cout << "Writing image to " << filename << '\n';


	stbi_write_bmp(filename.c_str(), width, height, 4, imgData);

	delete[] imgData;
}


