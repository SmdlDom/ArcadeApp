#include <SDL.h>
#include <cassert>
#include <cmath>

#include "Screen.h"
#include "Vec2D.h"
#include "Line2D.h"

void Screen::ClearScreen() {
	assert(_optrWindow);
	if(_optrWindow) SDL_FillRect(_noptrWindowSurface, nullptr, _clearColor.GetPixelColor());
}

Screen::Screen() : _width(0), _height(0), _optrWindow(nullptr), _noptrWindowSurface(nullptr) {}

Screen::~Screen() {
	if (_optrWindow) {
		SDL_DestroyWindow(_optrWindow);
		_optrWindow = nullptr;
	}
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag) {
	//Set the window
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}

	_width = w;
	_height = h;

	_optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   _width * mag, _height * mag, 0);

	if (_optrWindow) {
		_noptrWindowSurface = SDL_GetWindowSurface(_optrWindow);

		SDL_PixelFormat* pixelFormat = _noptrWindowSurface->format;
		Color::InitColorFormat(pixelFormat);
		_clearColor = Color::Black();

		_backBuffer.Init(pixelFormat->format, _width, _height);
		_backBuffer.Clear(_clearColor);
	}

	return _optrWindow;
}

void Screen::SwapScreens() {
	assert(_optrWindow);
	if (_optrWindow) {
		ClearScreen();

		SDL_BlitScaled(_backBuffer.GetSurface(), nullptr, _noptrWindowSurface, nullptr);
		SDL_UpdateWindowSurface(_optrWindow);

		_backBuffer.Clear(_clearColor);
	}
}

void Screen::Draw(int x, int y, const Color& color) {
	assert(_optrWindow);
	if (_optrWindow) {
		_backBuffer.SetPixel(color, x, y);
	}
}

void Screen::Draw(const Vec2D& point, const Color& color) {
	assert(_optrWindow);
	if (_optrWindow) {
		_backBuffer.SetPixel(color, point.GetX(), point.GetY());
	}
}

void Screen::Draw(const Line2D& line, const Color& color) {
	assert(_optrWindow);
	if (_optrWindow) {
		int dx, dy;
		int x0 = roundf(line.GetP0().GetX());
		int y0 = roundf(line.GetP0().GetY());
		int x1 = roundf(line.GetP1().GetX());
		int y1 = roundf(line.GetP1().GetY());

		dx = x1 - x0;
		dy = y1 - y0;

		signed const char ix((dx > 0) - (dx < 0));
		signed const char iy((dy > 0) - (dy < 0));

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		Draw(x0, y0, color);

		if (dx >= dy) {
			int d = dy - dx / 2;

			while (x0 != x1) {
				if (d >= 0) {
					d -= dx;
					y0 += iy;
				}
				d += dy;
				x0 += ix;

				Draw(x0, y0, color);
			}
		} else {
			int d = dx - dy / 2;

			while (y0 != y1) {
				if (d >= 0) {
					d -= dy;
					x0 += ix;
				}

				d += dx; 
				y0 += iy;

				Draw(x0, y0, color);
			}
		}
	}
}
