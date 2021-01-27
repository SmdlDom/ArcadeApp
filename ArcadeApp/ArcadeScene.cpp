#include "ArcadeScene.h"
#include "Color.h"
#include "Screen.h"
#include "GameController.h"
#include <iostream>
#include "App.h"
#include "GameScene.h"
#include "BreakOut.h"
#include "NotImplementedScene.h"

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
	switch (game) {
		case TETRIS:
		{

		}
		break;

		case BREAK_OUT:
		{
			std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();
			std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));
			return breakoutScene;
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
	}

	std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();
	return notImplementedScene;
}

ArcadeScene::ArcadeScene() :ButtonOptionsScene({ "Tetris","Break Out !", "Asteroids", "!Pac-man" }, Color::Cyan()) {}

void ArcadeScene::Init() {
	std::vector<Button::ButtonAction> actions;

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(TETRIS));
	});

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(BREAK_OUT));
	});
	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(ASTEROIDS));
	});
	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(PACMAN));
	});

	SetButtonActions(actions);
	ButtonOptionsScene::Init();

	//temp
	{
		
		_spriteSheet.Load("PacmanSprites");
		_sprite.Init(App::Singleton().GetBasePath() + "Assets\\Pacman_animations.txt", _spriteSheet);
		_sprite.SetAnimation("move_left", true);
	}
}

void ArcadeScene::Update(uint32_t dt) {
	_sprite.Update(dt);
}

void ArcadeScene::Draw(Screen& theScreen) {
	ButtonOptionsScene::Draw(theScreen);
	_sprite.Draw(theScreen);
}

const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade";
	return sceneName;
}
