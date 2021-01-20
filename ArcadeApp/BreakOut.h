#pragma once

#ifndef GAMES_BREAKOUT_BREAKOUT_H_
#define GAMES_BREAKOUT_BREAKOUT_H_

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"

class BreakOut : public Game {
private:
	const Vec2D INITIAL_BALL_VEL = Vec2D(200, -200);
	Paddle _paddle;
	Ball _ball;
	LevelBoundary _levelBoundary;

	void ResetGame();

public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
};


#endif /* GAMES_BREAKOUT_BREAKOUT_H_*/