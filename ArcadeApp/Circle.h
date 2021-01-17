#pragma once

#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include "Shape.h"

class Circle: public Shape {
private:
	float _radius;

public:
	Circle();
	Circle(const Vec2D& center, float radius);

	inline virtual Vec2D GetCenterPoint() const override { return _points[0]; }
	inline float GetRadius() const { return _radius; }
	inline void SetRadius(float radius) { _radius = radius; }
	inline void MoveTo(const Vec2D& position) { _points[0] = position; }

	bool Intersect(const Circle& otherCircle) const;
	bool ContainsPoint(const Vec2D& point) const;
};

#endif SHAPES_CIRCLE_H_