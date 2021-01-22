#pragma once

#ifndef GAMES_BREAKOUT_BREAKOUT_H_
#define GAMES_BREAKOUT_BREAKOUT_H_

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"
#include <vector>

enum BreakOutGameState {
	IN_PLAY = 0,
	IN_SERVE,
	IN_GAME_OVER
};

class BreakOut : public Game {
private:
	static const int NUM_LIVES = 3;
	const  float INITIAL_BALL_SPEED = 200;
	const Vec2D INITIAL_BALL_VEL = Vec2D(200, -200);
	Paddle _paddle;
	Ball _ball;
	LevelBoundary _levelBoundary;
	std::vector<BreakoutGameLevel> _levels;
	size_t _currentLevel;
	BreakOutGameState _gameState;
	int _lives;
	float _yCutoff;

	void ResetGame(size_t toLevel = 0, int lives = NUM_LIVES);
	BreakoutGameLevel& GetCurrentLevel() { return _levels[_currentLevel]; }
	void SetToServeState();

	bool IsBallPassedCutOffY() const;
	void ReduceLifeByOne();
	bool IsGameOver() const { return _lives < 0; }

public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
};


#endif /* GAMES_BREAKOUT_BREAKOUT_H_*/