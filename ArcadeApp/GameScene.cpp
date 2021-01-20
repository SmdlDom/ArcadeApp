#include "GameScene.h"

GameScene::GameScene(std::unique_ptr<Game> optrGame):_game(std::move(optrGame)) {}

void GameScene::Init() {
	_game->Init(_gameController);
}

void GameScene::Update(uint32_t dt) {
	_game->Update(dt);
}

void GameScene::Draw(Screen& screen) {
	_game->Draw(screen);
}

const std::string& GameScene::GetSceneName() const {
	return _game->GetName();
}
