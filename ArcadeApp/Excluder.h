#pragma once

#ifndef GAMES_BREAKOUT_EXCLUDER_H_
#define GAMES_BREAKOUT_EXCLUDER_H_

#include "AARectangle.h"
#include "BoundaryEdge.h"

class Excluder {
private:
	AARectangle _AARect;
	BoundaryEdge _edges[NUM_EDGES];
	bool _reverseNormals;

	void SetupEdges();

public:
	virtual ~Excluder() {}
	void Init(const AARectangle& rect, bool reverseNormals = false);

	//We'll encapsulated a circle inside a rectangle to handle collision of the ball
	bool HasCollided(const AARectangle& rect, BoundaryEdge& edge) const;
	Vec2D GetCollisionOffset(const AARectangle& rect) const;

	inline const AARectangle& GetAARectangle() const { return _AARect; }
	void MoveBy(const Vec2D& delta);
	void MoveTo(const Vec2D& point);
	const BoundaryEdge& GetEdge(EdgeType edge) const;
};

#endif /* GAMES_BREAKOUT_EXCLUDER_H_*/