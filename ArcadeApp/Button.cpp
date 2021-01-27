#include "Button.h"
#include "Screen.h"

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor):
	_bitmapFont(bitmapFont), _textColor(textColor), _highlightColor(highlightColor), _title(""), _highlighted(false), _action(nullptr){}

void Button::Init(Vec2D topLeft, unsigned int width, unsigned int height) {
	_bBox = AARectangle(topLeft, width, height);
}

void Button::Draw(Screen& theScreen) {
	theScreen.Draw(_bitmapFont, _title, _bitmapFont.GetDrawPosition(_title, _bBox, BFXA_CENTER, BFYA_CENTER), _textColor);
	if (_highlighted) theScreen.Draw(_bBox, _highlightColor);
}

void Button::ExecuteAction() {
	_action();
}