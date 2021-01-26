#pragma once

#ifndef GRAPHICS_BITMAPFONT_H_
#define GRAPHICS_BITMAPFONT_H_

#include <stdint.h>
#include "SpriteSheet.h"
#include "Utils.h"

class Vec2D;
class AARectangle;

enum BitmapFontXAligment {
	BFXA_LEFT = 0,
	BFXA_CENTER,
	BFXA_RIGHT
};

enum BitmapFontYAligment {
	BFYA_TOP = 0,
	BFYA_CENTER,
	BFYA_BOTTOM
};

class BitmapFont {
private:
	SpriteSheet _fontSheet;
	
public:
	BitmapFont();

	bool Load(const std::string& name);
	Size GetSizeOf(const std::string& str) const;
	Vec2D GetDrawPosition(const std::string& str, const AARectangle& box,
						  BitmapFontXAligment xAlign = BFXA_LEFT,
						  BitmapFontYAligment yAlign = BFYA_TOP) const;
	inline const SpriteSheet& GetSpriteSheet() const { return _fontSheet; }
	inline const uint32_t GetFontSpacingBetweenLetters() const { return 2; }
	inline const uint32_t GetFontSpacingBetweenWords() const { return 5; }
};

#endif /* GRAPHICS_BITMAPFONT_H_*/