#pragma once

#ifndef GAMES_BREAKOUT_LEVELBOUNDARY_H_
#define GAMES_BREAKOUT_LEVELBOUNDARY_H_

#include "Excluder.h"

class AARectangle;
class Ball;

class LevelBoundary {
private:
	Excluder _includer;

	bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;

public: 
	LevelBoundary() {};
	LevelBoundary(const AARectangle& boundary);
	bool HasCollided(const Ball& ball, BoundaryEdge& edge);
	inline const AARectangle& GetAARectangle() const { return _includer.GetAARectangle(); }


};





#endif /* GAMES_BREAKOUT_LEVELBOUNDARY_H_*/