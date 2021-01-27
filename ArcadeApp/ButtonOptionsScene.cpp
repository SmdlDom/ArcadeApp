#include "ButtonOptionsScene.h"
#include "App.h"
#include "BitmapFont.h"
#include "Utils.h"
#include <iostream>


ButtonOptionsScene::ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor) :
	_highlightedOption(0) {
	const BitmapFont& font = App::Singleton().GetFont();

	for (size_t i = 0; i < optionNames.size(); ++i) {
		Button b = { font, textColor };
		_buttons.push_back(b);
		_buttons.back().SetButtonText(optionNames[i]);
	}

	if (optionNames.size() > 0) {
		_buttons[_highlightedOption].SetHighlighted(true);
	}
}

void ButtonOptionsScene::Init() {
	ButtonAction upAction;
	upAction.key = GameController::UpKey();
	upAction.action = [this](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
		    SetPreviousButtonHighlighted();
		}
	};

	_gameController.AddInputActionForKey(upAction);


	ButtonAction downAction;
	downAction.key = GameController::DownKey();
	downAction.action = [this](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
			SetNextButtonHighlighted();
		}
	};

	_gameController.AddInputActionForKey(downAction);

	ButtonAction acceptAction;
	acceptAction.key = GameController::ActionKey();
	acceptAction.action = [this](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
			ExecuteCurrentButtonAction();
		}
	};

	_gameController.AddInputActionForKey(acceptAction);


	uint32_t height = App::Singleton().Height();
	uint32_t width = App::Singleton().Width();

	const BitmapFont& font = App::Singleton().GetFont();

	Size fontSize = font.GetSizeOf(_buttons[0].GetButtonText());

	const int BUTTON_PAD = 10;

	unsigned int buttonHeight = fontSize.height + BUTTON_PAD * 2;

	uint32_t maxButtonWidth = fontSize.width;

	for (const auto& button : _buttons) {
		Size s = font.GetSizeOf(button.GetButtonText());

		if (s.width > maxButtonWidth) {
			maxButtonWidth = s.width;
		}
	}

	maxButtonWidth += BUTTON_PAD * 2;

	const uint32_t Y_PAD = 1;

	uint32_t yOffset = height / 2 - ((buttonHeight + Y_PAD) * static_cast<uint32_t>(_buttons.size())) / 2;

	for (auto& button : _buttons) {
		button.Init(Vec2D(width / 2 - maxButtonWidth / 2, yOffset), maxButtonWidth, buttonHeight);

		yOffset += buttonHeight + Y_PAD;
	}

	_buttons[_highlightedOption].SetHighlighted(true);
}

void ButtonOptionsScene::Update(uint32_t dt) {

}

void ButtonOptionsScene::Draw(Screen& theScreen) {
	for (auto& button : _buttons) {
		button.Draw(theScreen);
	}
}

void ButtonOptionsScene::SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions) {
	for (size_t i = 0; i < _buttons.size(); ++i) {
		_buttons[i].SetButtonAction(buttonActions[i]);
	}
}

void ButtonOptionsScene::SetNextButtonHighlighted() {
	_highlightedOption = (_highlightedOption + 1) % _buttons.size();

	HighlightCurrentButton();
}

void ButtonOptionsScene::SetPreviousButtonHighlighted() {
	--_highlightedOption;

	if (_highlightedOption < 0) {
		_highlightedOption = static_cast<int>(_buttons.size()) - 1;
	}

	HighlightCurrentButton();
}

void ButtonOptionsScene::ExecuteCurrentButtonAction() {
	_buttons[_highlightedOption].ExecuteAction();
}

void ButtonOptionsScene::HighlightCurrentButton() {
	for (auto& button : _buttons) {
		button.SetHighlighted(false);
	}

	_buttons[_highlightedOption].SetHighlighted(true);
}
