#include "ArcadeScene.h"
#include "Line2D.h"
#include "Circle.h"
#include "AARectangle.h"
#include "Triangle.h"
#include "Color.h"
#include "Screen.h"
#include "GameController.h"
#include <iostream>
#include "App.h"

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
	switch (game) {
		case TETRIS:
		{

		}
		break;

		case BREAK_OUT:
		{

		}
		break;

		case ASTEROIDS:
		{

		}
		break;

		case PACMAN: 
		{

		}
		break;

		default: 
		{

		}
		break;
	}
	return nullptr;
}

ArcadeScene::ArcadeScene() {

}

void ArcadeScene::Init() {

	_tempSS.Load("ArcadeFont");

	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
			std::cout << "action button was pressed!" << std::endl;
		}
	};

	_gameController.AddInputActionForKey(action);

    MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position) {
		if (GameController::IsPressed(state)) {
			std::cout << "Left Mouse button pressed!" << std::endl;
		}
	};

	_gameController.AddMouseButtonAction(mouseAction);

	_gameController.SetMouseMovedAction([](const MousePosition& mousePosition) {
		std::cout << "Mouse position x: " << mousePosition.xPos << ", y: " << mousePosition.yPos << std::endl;
	 });
}

void ArcadeScene::Update(uint32_t dt) {}

void ArcadeScene::Draw(Screen& theScreen) {
	theScreen.Draw(_tempSS, "w", Vec2D::Zero);
}

const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}
