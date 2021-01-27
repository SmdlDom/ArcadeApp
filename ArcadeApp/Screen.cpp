#include <SDL.h>
#include <cassert>
#include <cmath>
#include <algorithm>

#include "Screen.h"
#include "Vec2D.h"
#include "Line2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"
#include "Utils.h"
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "BitmapFont.h"

void Screen::ClearScreen() {
	assert(_optrWindow);
	if (_optrWindow) {
		if (_fast) SDL_RenderClear(_renderer);
		else SDL_FillRect(_noptrWindowSurface, nullptr, _clearColor.GetPixelColor());	
	}
}

void Screen::FillPoly(const std::vector<Vec2D>& points, FillPolyFunc func) {
	if (points.size() > 0) {
		float top = points[0].GetY();
		float bottom = points[0].GetY();
		float right = points[0].GetX();
		float left = points[0].GetX();

		for (size_t i = 1; i < points.size(); ++i) {
			if (points[i].GetY() < top) {
				top = points[i].GetY();
			}

			if (points[i].GetY() > bottom) {
				bottom = points[i].GetY();
			}

			if (points[i].GetX() < left) {
				left = points[i].GetX();
			}

			if (points[i].GetX() > right) {
				right = points[i].GetX();
			}
		}


		for (int pixelY = top; pixelY < bottom; ++pixelY) {
			std::vector<float> nodeXVec;

			size_t j = points.size() - 1;

			for (size_t i = 0; i < points.size(); ++i) {
				float pointiY = points[i].GetY();
				float pointjY = points[j].GetY();


				if ((pointiY <= (float) pixelY && pointjY > (float)pixelY) || (pointjY <= (float) pixelY && pointiY > (float)pixelY)) {
					float denom = pointjY - pointiY;
					if (IsEqual(denom, 0)) {
						continue;
					}

					float x = points[i].GetX() + (pixelY - pointiY) / (denom) * (points[j].GetX() - points[i].GetX());
					nodeXVec.push_back(x);
				}

				j = i;
			}

			std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

			for (size_t k = 0; k < nodeXVec.size(); k += 2) {
				if (nodeXVec[k] > right) {
					break;
				}

				if (nodeXVec[k + 1] > left) {
					if (nodeXVec[k] < left) {
						nodeXVec[k] = left;
					}
					if (nodeXVec[k + 1] > right) {
						nodeXVec[k + 1] = right;
					}

					for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; ++pixelX) {
						Draw(pixelX, pixelY, func(pixelX, pixelY));
					}
				}
			}
		}
	}
}

Screen::Screen() : _width(0), _height(0), _optrWindow(nullptr), _noptrWindowSurface(nullptr), 
                   _renderer(nullptr), _pixelFormat(nullptr), _texture(nullptr){}

Screen::~Screen() {

	if (_pixelFormat) {
		SDL_FreeFormat(_pixelFormat);
		_pixelFormat = nullptr;
	}

	if (_texture) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}

	if (_renderer) {
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}

	if (_optrWindow) {
		SDL_DestroyWindow(_optrWindow);
		_optrWindow = nullptr;
	}
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag, bool fast) {
	
	_fast = fast;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}

	_width = w;
	_height = h;

	_optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								   _width * mag, _height * mag, 0);

	if (_optrWindow) {
		int8_t rClear = 0;
		int8_t gClear = 0;
		int8_t bClear = 0;
		int8_t aClear = 255;

		if (_fast) {
			_renderer = SDL_CreateRenderer(_optrWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (_renderer == nullptr) {
				std::cout << "SDL_CreateRenderer failed" << std::endl;
				return nullptr;
			}

			SDL_SetRenderDrawColor(_renderer, rClear, gClear, bClear, aClear);
		} else {
			_noptrWindowSurface = SDL_GetWindowSurface(_optrWindow);
		}

		_pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

		if (_fast) {
			_texture = SDL_CreateTexture(_renderer, _pixelFormat->format, SDL_TEXTUREACCESS_STREAMING, w, h);
		}

		Color::InitColorFormat(_pixelFormat);
		_clearColor = Color(rClear, gClear, bClear, aClear);

		_backBuffer.Init(_pixelFormat->format, _width, _height);
		_backBuffer.Clear(_clearColor);
	}

	return _optrWindow;
}

void Screen::SwapScreens() {
	assert(_optrWindow);
	if (_optrWindow) {
		ClearScreen();

		if (_fast) {
			uint8_t* textureData = nullptr;
			int texturePitch = 0;

			if (SDL_LockTexture(_texture, nullptr, (void**) &textureData, &texturePitch) >= 0) {
				SDL_Surface* surface = _backBuffer.GetSurface();

				memcpy(textureData, surface->pixels, surface->w * surface->h * _pixelFormat->BytesPerPixel);

				SDL_UnlockTexture(_texture);
				SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
				SDL_RenderPresent(_renderer);
			}
		} else {
			SDL_BlitScaled(_backBuffer.GetSurface(), nullptr, _noptrWindowSurface, nullptr);
			SDL_UpdateWindowSurface(_optrWindow);

			_backBuffer.Clear(_clearColor);
		}
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

void Screen::Draw(const Triangle& triangle, const Color& color, bool fill, const Color& fillColor) {

	if (fill) FillPoly(triangle.GetPoints(), [fillColor](uint32_t x, uint32_t y) {return fillColor; });
	

	Line2D p0p1 = Line2D(triangle.GetP0(), triangle.GetP1());
	Line2D p1p2 = Line2D(triangle.GetP1(), triangle.GetP2());
	Line2D p2p0 = Line2D(triangle.GetP2(), triangle.GetP0());

	Draw(p0p1, color);
	Draw(p1p2, color);
	Draw(p2p0, color);
}

void Screen::Draw(const AARectangle& rect, const Color& color, bool fill, const Color& fillColor) {

	if (fill) FillPoly(rect.GetPoints(), [fillColor](uint32_t x, uint32_t y) {return fillColor; });

	std::vector<Vec2D> points = rect.GetPoints();

	Line2D p0p1 = Line2D(points[0], points[1]);
	Line2D p1p2 = Line2D(points[1], points[2]);
	Line2D p2p3 = Line2D(points[2], points[3]);
	Line2D p3p0 = Line2D(points[3], points[0]);

	Draw(p0p1, color);
	Draw(p1p2, color);
	Draw(p2p3, color);
	Draw(p3p0, color);

}

void Screen::Draw(const Circle& circle, const Color& color, bool fill, const Color& fillColor) {
	static unsigned int NUM_CIRCLE_SEGMENTS = 60;

	std::vector<Vec2D> circlePoints;
	std::vector<Line2D> lines;

	float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

	Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(),
					 circle.GetCenterPoint().GetY() + circle.GetRadius());
	Vec2D p1 = p0;
	Line2D nextLineToDraw;

	for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; ++i) {
		p1.Rotate(angle, circle.GetCenterPoint());
		nextLineToDraw.SetP1(p1);
		nextLineToDraw.SetP0(p0);

		lines.push_back(nextLineToDraw);
		p0 = p1;
		circlePoints.push_back(p0);
	}

	if (fill) FillPoly(circlePoints, [fillColor](uint32_t x, uint32_t y) {return fillColor; });

	for (const Line2D& line : lines) Draw(line, color);
}

void Screen::Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor) {

	float rVal = static_cast<float>(overlayColor.GetRed()) / 255.0f;
	float gVal = static_cast<float>(overlayColor.GetGreen()) / 255.0f;
	float bVal = static_cast<float>(overlayColor.GetBlue()) / 255.0f;
	float aVal = static_cast<float>(overlayColor.GetAlpha()) / 255.0f;

	uint32_t width = sprite.width;
	uint32_t height = sprite.height;

	const std::vector<Color>& pixels = image.GetPixels();

	auto topLeft = pos;
	auto topRight = pos + Vec2D(width, 0);
	auto bottomLeft = pos + Vec2D(0, height);
	auto bottomRight = pos + Vec2D(width, height);

	std::vector<Vec2D> points = { topLeft, bottomLeft, bottomRight, topRight };

	Vec2D xAxis = topRight - topLeft;
	Vec2D yAxis = bottomLeft - topLeft;

	const float invXAxisLengthSq = 1.0f / xAxis.Mag2();
	const float invYAxisLengthSq = 1.0f / yAxis.Mag2();

	FillPoly(points, [&](uint32_t px, uint32_t py){
			 
		Vec2D p = { static_cast<float> (px), static_cast<float> (py) };
		Vec2D d = p - topLeft;

		float u = invXAxisLengthSq * d.Dot(xAxis);
		float v = invYAxisLengthSq * d.Dot(yAxis);

		u = Clamp(u, 0.0f, 1.0f);
		v = Clamp(v, 0.0f, 1.0f);

		float tx = roundf(u * static_cast<float>(sprite.width));
		float ty = roundf(v * static_cast<float>(sprite.width));

		Color imageColor = pixels[GetIndex(image.GetWidth(), ty + sprite.yPos, tx + sprite.xPos)];
		Color newColor = { static_cast<uint8_t> (imageColor.GetRed() * rVal),static_cast<uint8_t> (imageColor.GetGreen() * gVal),
			               static_cast<uint8_t> (imageColor.GetBlue() * bVal), static_cast<uint8_t> (imageColor.GetAlpha() * aVal) };

		return newColor;
	});
}

void Screen::Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor) {
	Draw(ss.GetBMPImage(), ss.GetSprite(spriteName), pos, overlayColor);
}

void Screen::Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor) {
	uint32_t xPos = pos.GetX();

	const SpriteSheet& ss = font.GetSpriteSheet();

	for (char c : textLine) {
		if (c == ' ') {
			xPos += font.GetFontSpacingBetweenWords();
			continue;
		}

		Sprite sprite = ss.GetSprite(std::string("") + c);

		Draw(ss.GetBMPImage(), sprite, Vec2D(xPos, pos.GetY()), overlayColor);

		xPos += sprite.width;

		xPos += font.GetFontSpacingBetweenLetters();
	}
}

