#include "ArcadeScene.h"
#include "Line2D.h"
#include "Circle.h"
#include "AARectangle.h"
#include "Triangle.h"
#include "Color.h"
#include "Screen.h"
#include "GameController.h"
#include <iostream>

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
	Line2D line = { Vec2D(0,0), Vec2D(theScreen.Width(), theScreen.Height()) };
	Triangle triangle = { Vec2D(60,10), Vec2D(10,110), Vec2D(110,110) };
	AARectangle rect = { Vec2D(theScreen.Width() / 2 - 25, theScreen.Height() / 2 - 25), 50, 50 };
	Circle circle = { Vec2D(theScreen.Width() / 2 + 50, theScreen.Height() / 2 + 50), 50 };

	theScreen.Draw(circle, Color(255, 0, 0, 150), true, Color(255, 0, 0, 150));
	theScreen.Draw(rect, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
	theScreen.Draw(triangle, Color::Red(), true, Color::Red());
}

const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}
