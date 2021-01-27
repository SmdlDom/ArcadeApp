#pragma once

#ifndef APP_BUTTON_H_
#define APP_BUTTON_H_

#include <string>
#include <functional>
#include "AARectangle.h"
#include "Color.h"
#include "BitmapFont.h"

class Screen;


class Button {
public: 
	using ButtonAction = std::function<void(void)>;
private:
	const BitmapFont& _bitmapFont;
	std::string _title;
	AARectangle _bBox;

	bool _highlighted;
    ButtonAction _action;
	Color _highlightColor;
	Color _textColor;

public:
	Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor = Color::White());
	void Init(Vec2D topLeft, unsigned int width, unsigned int height);
	void Draw(Screen& theScreen);
	void ExecuteAction();

	inline void SetButtonText(const std::string& text) { _title = text; }
	inline const std::string& GetButtonText() const { return _title; }
	inline void SetHighlighted(bool highlighted) { _highlighted = highlighted; }
	inline bool IsHighlighted() const { return _highlighted; }
	inline void SetButtonAction(ButtonAction action) { _action = action; }

};


#endif /* APP_BUTTON_H_*/