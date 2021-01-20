#include "LevelBoundary.h"
#include "Ball.h"

bool LevelBoundary::HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const {
	return edge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius();
}

LevelBoundary::LevelBoundary(const AARectangle& boundary) {
	_includer.Init(boundary, true);
}

bool LevelBoundary::HasCollided(const Ball& ball, BoundaryEdge& edge) {
	for (int i = 0; i < NUM_EDGES; ++i) {
		BoundaryEdge collisionEdge = _includer.GetEdge(static_cast<EdgeType>(i));
		if (HasCollidedWithEdge(ball, collisionEdge)) {
			edge = collisionEdge;
			return true;
		}
	}

	return false;
}
