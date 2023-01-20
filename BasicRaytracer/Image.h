#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

#include "Color.h"


class Image
{
protected:
	int width, height;
	Color* data;

public:
	Image(int width, int height);

	virtual ~Image();

	int getWidth() const;
	int getHeight() const;
	Color* getPixel(int x, int y);

	void saveImage(std::string filename, float exposure, float gamma) const;
};

#endif