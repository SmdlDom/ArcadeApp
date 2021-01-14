#pragma once

#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include <stdint.h>
#include "ScreenBuffer.h"
#include "Color.h"

class Vec2D;
struct SDL_Window;
struct SDL_Surface;

class Screen {
	Screen(const Screen& screen);
	Screen& operator=(const Screen& screen);

	uint32_t _width;
	uint32_t _height;

	Color _clearColor;
	ScreenBuffer _backBuffer;

	SDL_Window* _optrWindow;
	SDL_Surface* _noptrWindowSurface;

	void ClearScreen();

public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreens();

	inline void SetClearColor(const Color& clearColor) { _clearColor = clearColor; }
	inline uint32_t Width() const { return _width; }
	inline uint32_t Height() const { return _height; }

	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
};


#endif /* GRAPHICS_SCREEN_H_*/
