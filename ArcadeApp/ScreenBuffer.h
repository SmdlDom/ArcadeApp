#pragma once

#ifndef GRAPHICS_SCREENBUFFER_H_
#define GRAPHICS_SCREENBUFFER_H_

#include <stdint.h>
#include "Color.h"

struct SDL_Surface;

class ScreenBuffer {

	SDL_Surface* _surface;
	uint32_t GetIndex(int r, int c);

public:
	ScreenBuffer();
	ScreenBuffer(const ScreenBuffer& screenBuffer);
	~ScreenBuffer();

	ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

	void Init(uint32_t format, uint32_t w, uint32_t h);

	inline SDL_Surface* GetSurface() { return _surface; }

	void Clear(const Color& c = Color::Black());

	void SetPixel(const Color& color, int x, int y);
};


#endif /* GRAPHICS_SCREENBUFFER_H_*/
