#include <SDL.h>
#include <cassert>

#include "Screen.h"
#include "Vec2D.h"

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
