#pragma once

#ifndef SCENES_BUTTONOPTIONSCENE_H_
#define SCENES_BUTTONOPTIONSCENE_H_

#include <string>
#include <vector>
#include "Scene.h"
#include "Button.h"

class Screen;

class ButtonOptionsScene : public Scene {
private:
	std::vector<Button> _buttons;
	int _highlightedOption;

	void SetNextButtonHighlighted();
	void SetPreviousButtonHighlighted();
	void ExecuteCurrentButtonAction();
	void HighlightCurrentButton();
public: 
	ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor);

	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;

	void SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions);
};

#endif /*SCENES_BUTTONOPTIONSCENE_H_*/
