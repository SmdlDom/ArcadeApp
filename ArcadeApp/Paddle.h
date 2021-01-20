#pragma once

#ifndef GAMES_BREAKOUT_PADDLE_H_
#define GAMES_BREAKOUT_PADDLE_H_

#include "Excluder.h"
#include <stdint.h>

class Screen;
class Ball;

enum PaddleDirection {
	LEFT = 1 << 0,
	RIGHT = 1 << 1

};


class Paddle : public Excluder {
private:
	uint32_t _direction; //direction we're moving
	AARectangle _boundary; //boundary that the paddle is confined to
	const float VELOCITY = 100.0f; //pixels/sec
	const float CORNER_BOUNCE_AMT = 0.2f;

public:
	static const uint32_t PADDLE_WIDTH = 50;
	static const uint32_t PADDLE_HEIGHT = 10;

	void Init(const AARectangle& rect, const AARectangle& boundary);
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);

	bool Bounce(Ball& ball);

	inline bool IsMovingLeft() const { return _direction == PaddleDirection::LEFT; }
	inline bool IsMovingRight() const { return _direction == PaddleDirection::RIGHT; }

	inline void SetMovementDirection(PaddleDirection dir) {_direction |= dir; }
	inline void UnsetMovementDirection(PaddleDirection dir) { _direction &= ~dir; }
	inline void StopMovement() { _direction = 0; }

};

#endif /* GAMES_BREAKOUT_PADDLE_H_*/  