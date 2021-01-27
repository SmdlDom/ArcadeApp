#pragma once

#ifndef SCENES_ARCADESCENE_H_
#define SCENES_ARCADESCENE_H_

#include <memory>
#include "ButtonOptionsScene.h"
#include "AnimatedSprite.h"

enum eGame {
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class Screen;

class ArcadeScene : public ButtonOptionsScene {
private:
	std::unique_ptr<Scene> GetScene(eGame game);

	//temp
	AnimatedSprite _sprite;
	SpriteSheet _spriteSheet;
	
public:
	ArcadeScene();
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;
};


#endif /* SCENES_ARCADESCENE_H_*/