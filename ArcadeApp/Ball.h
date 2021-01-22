#pragma once

#ifndef GAMES_BREAKOUT_BALL_H_
#define GAMES_BREAKOUT_BALL_H_

#include "AARectangle.h"
#include <stdint.h>


class Screen;
struct BoundaryEdge;

class Ball {
private:
	AARectangle _bBox;
	Vec2D _velocity;

	static const float RADIUS;

public:
	Ball();
	Ball(const Vec2D& pos, float radius);

	void Update(uint32_t dt);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
	inline void Stop() { _velocity = Vec2D::Zero; }
	void MoveTo(const Vec2D& point);

	void Bounce(const BoundaryEdge& edge);

	inline const AARectangle GetBoundRect() const { return _bBox; }
	inline void SetVelocity(const Vec2D& vel) { _velocity = vel; }
	inline Vec2D GetVelocity() const { return _velocity; }
	inline float GetRadius() const { return RADIUS; }
	inline Vec2D GetPosition() const { return _bBox.GetCenterPoint(); }
};

#endif /* GAMES_BREAKOUT_BALL_H_*/