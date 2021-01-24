#include "BMPImage.h"
#include <SDL.h>

BMPImage::BMPImage(): _width(0), _height(0) {}

bool BMPImage::Load(const std::string& path) {
	SDL_Surface* bmpSurface = SDL_LoadBMP(path.c_str());

	if (bmpSurface == nullptr) {
		return false;
	}

	_width = bmpSurface->w;
	_height = bmpSurface->h;

	uint32_t lengthOfFile = _width * _height;

	_pixels.reserve(lengthOfFile);

	SDL_LockSurface(bmpSurface);

	uint32_t* pixels = static_cast<uint32_t*>(bmpSurface->pixels);

	for (uint32_t i = 0; i < lengthOfFile; ++i) {
		_pixels.push_back(Color(pixels[i]));
	}
	SDL_UnlockSurface(bmpSurface);
	SDL_FreeSurface(bmpSurface);

	return true;
}
