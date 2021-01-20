#pragma once

#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "Scene.h"
#include "Game.h"
#include <memory>

class GameScene : public Scene {
private: 
	std::unique_ptr<Game> _game;

public:
	GameScene(std::unique_ptr<Game> optrGame);
	virtual ~GameScene() {}
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;

	virtual const std::string& GetSceneName() const override;
};

#endif /* SCENES_GAMESCENE_H_*/