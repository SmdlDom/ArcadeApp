#pragma once
#ifndef SHAPES_LINE2D_H_
#define SHAPES_LINE2D_H_

#include "Vec2D.h"

class Line2D {
	Vec2D _p0;
	Vec2D _p1;

public:
	Line2D();
	Line2D(float x0, float y0, float x1, float y1);
	Line2D(const Vec2D& p0, const Vec2D& p1);

	inline const Vec2D& GetP0() const { return _p0; }
	inline const Vec2D& GetP1() const { return _p1; }

	inline void SetP0(const Vec2D& p0) { _p0 = p0; }
	inline void SetP1(const Vec2D& p1) { _p1 = p1; }

	bool operator==(const Line2D& line) const;

	float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const;

	Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment = false) const;
	Vec2D Midpoint() const;

	float Slope() const;
	float Length() const;

};

#endif /* SHAPES_LINE2D_H_*/