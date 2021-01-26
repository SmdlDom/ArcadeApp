#pragma once

#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include <stdint.h>
#include <vector>
#include <string>
#include <functional>
#include "ScreenBuffer.h"
#include "Color.h"


class Vec2D;
class Line2D;
class Triangle;
class AARectangle;
class Circle;
class BMPImage;
class SpriteSheet;
class BitmapFont;

struct Sprite;

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;


class Screen {
	Screen(const Screen& screen);
	Screen& operator=(const Screen& screen);

	uint32_t _width;
	uint32_t _height;

	Color _clearColor;
	ScreenBuffer _backBuffer;

	SDL_Window* _optrWindow;
	SDL_Surface* _noptrWindowSurface;
	SDL_Renderer* _renderer;
	SDL_PixelFormat* _pixelFormat;
	SDL_Texture* _texture;
	bool _fast;

	void ClearScreen();

	using FillPolyFunc = std::function<Color(uint32_t x, uint32_t y)>;

	void FillPoly(const std::vector<Vec2D>& points, FillPolyFunc func);

public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag, bool fast = true);
	void SwapScreens();

	inline void SetClearColor(const Color& clearColor) { _clearColor = clearColor; }
	inline uint32_t Width() const { return _width; }
	inline uint32_t Height() const { return _height; }

	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void Draw(const Line2D& line, const Color& color);

	void Draw(const Triangle& triangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const AARectangle& rect, const Color& color, bool fill = false, const Color& fillColor = Color::White());
	void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());

	void Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor = Color::White());
	void Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor = Color::White());
	void Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor = Color::White());
};


#endif /* GRAPHICS_SCREEN_H_*/
