#pragma once


#ifndef SHAPES_SHAPE_H_
#define SHAPES_SHAPE_H_

#include "Vec2D.h"
#include <vector>

class Shape {
public:
	virtual Vec2D GetCenterPoint() const = 0;
	virtual void MoveTo(const Vec2D& position) = 0;
	virtual ~Shape() {}
	inline virtual std::vector<Vec2D> GetPoints() const { return _points; }
	void MoveBy(const Vec2D& deltaOffset);

protected:
	std::vector<Vec2D> _points;
};

#endif /* SHAPES_SHAPE_H_*/