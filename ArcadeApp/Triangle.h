#pragma once


#ifndef SHAPES_TRIANGLE_H_
#define SHAPES_TRIANGLE_H_

#include "Shape.h"

class Triangle : public Shape {
private:
	float Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;

public:
	Triangle();
	Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

	inline void SetP0(const Vec2D& p0) { _points[0] = p0; }
	inline void SetP1(const Vec2D& p1) { _points[0] = p1; }
	inline void SetP2(const Vec2D& p2) { _points[0] = p2; }

	inline Vec2D GetP0() const { return _points[0]; }
	inline Vec2D GetP1() const { return _points[1]; }
	inline Vec2D GetP2() const { return _points[2]; }

	virtual Vec2D GetCenterPoint() const override;
	virtual void MoveTo(const Vec2D& position) override;

	float Area() const;

	bool ContainsPoint(const Vec2D& p) const;


};

#endif /* SHAPES_TRIANGLE_H_*/