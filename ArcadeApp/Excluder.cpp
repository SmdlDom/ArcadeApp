#include "Excluder.h"
#include "Utils.h"
#include <cmath>
#include <cassert>

void Excluder::SetupEdges() {
    _edges[TOP_EDGE].edge = { _AARect.GetTopLeftPoint().GetX(), _AARect.GetTopLeftPoint().GetY(),
                             _AARect.GetBottomRightPoint().GetX(), _AARect.GetTopLeftPoint().GetY()};
    _edges[TOP_EDGE].normal = UP_DIR;

    _edges[LEFT_EDGE].edge = { _AARect.GetTopLeftPoint().GetX(), _AARect.GetTopLeftPoint().GetY(),
                             _AARect.GetTopLeftPoint().GetX(), _AARect.GetBottomRightPoint().GetY() };
    _edges[LEFT_EDGE].normal = LEFT_DIR;

    _edges[RIGHT_EDGE].edge = { _AARect.GetBottomRightPoint().GetX(), _AARect.GetTopLeftPoint().GetY(),
                             _AARect.GetBottomRightPoint().GetX(), _AARect.GetBottomRightPoint().GetY() };
    _edges[RIGHT_EDGE].normal = RIGHT_DIR;

    _edges[BOTTOM_EDGE].edge = { _AARect.GetTopLeftPoint().GetX(), _AARect.GetBottomRightPoint().GetY(),
                             _AARect.GetBottomRightPoint().GetX(), _AARect.GetBottomRightPoint().GetY() };
    _edges[BOTTOM_EDGE].normal = DOWN_DIR;

    if (_reverseNormals) for (auto& edge : _edges) edge.normal = -edge.normal;
}

void Excluder::Init(const AARectangle& rect, bool reverseNormals) {
    _AARect = rect;
    _reverseNormals = reverseNormals;
    SetupEdges();
}

bool Excluder::HasCollided(const AARectangle& rect, BoundaryEdge& edge) const {
	if (_AARect.Intersect(rect)) {
		float yMin = _AARect.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ? _AARect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = _AARect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? _AARect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = yMax - yMin;

		float xMin = _AARect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? _AARect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = _AARect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? _AARect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();
		
		float xSize = xMax - xMin;

		if (xSize > ySize) {
			if (rect.GetCenterPoint().GetY() > _AARect.GetCenterPoint().GetY()) {
				edge = _edges[BOTTOM_EDGE];
			} else {
				edge = _edges[TOP_EDGE];
			}
		} else {
			if (rect.GetCenterPoint().GetX() < _AARect.GetCenterPoint().GetX()) {
				edge = _edges[LEFT_EDGE];
			} else {
				edge = _edges[RIGHT_EDGE];
			}
		}
		return true;
	}
	return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& rect) const {
	BoundaryEdge edge;
	Vec2D offset = Vec2D::Zero;

	if (HasCollided(rect, edge)) {
		float yMin = _AARect.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ? _AARect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = _AARect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? _AARect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = yMax - yMin;

		float xMin = _AARect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? _AARect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = _AARect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? _AARect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = xMax - xMin;

		if (!IsEqual(edge.normal.GetY(), 0)) {
			offset = (ySize + 1) * edge.normal;
		} else {
			offset = (xSize + 1) * edge.normal;
		}
	}

	return offset;
}

void Excluder::MoveBy(const Vec2D& delta) {
    _AARect.MoveBy(delta);
    SetupEdges();
}

void Excluder::MoveTo(const Vec2D& point) {
    _AARect.MoveTo(point);
    SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const {
    assert(edge != NUM_EDGES);
    return _edges[edge];
}
