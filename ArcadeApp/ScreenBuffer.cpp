#include "ScreenBuffer.h"
#include <SDL.h>
#include <cassert>

ScreenBuffer::ScreenBuffer(): _surface(nullptr) {}

ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenBuffer) {
	_surface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer._surface->w, screenBuffer._surface->h,
											  0, screenBuffer._surface->format->format);
	SDL_BlitSurface(screenBuffer._surface, nullptr, _surface, nullptr);
}

ScreenBuffer::~ScreenBuffer() {
	if (_surface) SDL_FreeSurface(_surface);
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screenBuffer) {
	if (this == &screenBuffer) return *this;

	if (_surface != nullptr) {
		SDL_FreeSurface(_surface);
		_surface = nullptr;
	}

	if (screenBuffer._surface != nullptr) {
		_surface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer._surface->w, screenBuffer._surface->h,
												  0, screenBuffer._surface->format->format);
		SDL_BlitSurface(screenBuffer._surface, nullptr, _surface, nullptr);
	}

	return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t w, uint32_t h) {
	_surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 0, format);
	Clear();
}

void ScreenBuffer::Clear(const Color& c) {
	assert(_surface);
	if (_surface) SDL_FillRect(_surface, nullptr, c.GetPixelColor());
}

void ScreenBuffer::SetPixel(const Color& color, int x, int y) {
	assert(_surface);
	if (_surface && (y < _surface->h && y >= 0 && x >= 0 && x < _surface->w)) {
		SDL_LockSurface(_surface);

		uint32_t* pixels = (uint32_t*) _surface->pixels;
		size_t index = GetIndex(y, x);
		Color surfaceColor = Color(pixels[index]);
		pixels[index] = Color::EvaluateMinueSourceAlpha(color, surfaceColor).GetPixelColor();

		SDL_UnlockSurface(_surface);
	}
}

uint32_t ScreenBuffer::GetIndex(int r, int c) {
	assert(_surface);
	if(_surface) return r * _surface->w + c;
	return 0;
}