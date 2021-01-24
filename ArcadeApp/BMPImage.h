#pragma once


#ifndef GRAPHICS_BMPIMAGE_H_
#define GRAPHICS_BMPIMAGE_H_


#include "Color.h"
#include <vector>
#include <string>
#include <stdint.h>

class BMPImage {
private:
	std::vector<Color> _pixels;
	uint32_t _width;
	uint32_t _height;

public:
	BMPImage();
	bool Load(const std::string& path);

	inline const std::vector<Color>& GetPixels() const { return _pixels; }
	inline uint32_t GetWidth() const { return _width; }
	inline uint32_t GetHeight() const { return _height; }
};


#endif /* GRAPHICS_BMPIMAGE_H_*/