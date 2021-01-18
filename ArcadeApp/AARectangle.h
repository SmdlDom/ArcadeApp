#pragma once

#ifndef SHAPES_AARECTANGLE_H_
#define SHAPES_AARECTANGLE_H_

#include "Shape.h"

class AARectangle : public Shape {

public:
	AARectangle();
	AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
	AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

	inline void SetTopLeftPoint(const Vec2D& topLeft) { _points[0] = topLeft; }
	inline void SetBottomRightPoint(const Vec2D& bottomRight) { _points[1] = bottomRight; }

	Vec2D GetTopLeftPoint() const { return _points[0]; }
	Vec2D GetBottomRightPoint() const { return _points[1]; }

	float GetWidth() const;
	float GetHeight() const;

	void MoveTo(const Vec2D& position) override;

	virtual Vec2D GetCenterPoint() const override;

	bool Intersect(const AARectangle& otherRect) const;
	bool ContainsPoint(const Vec2D& point) const;

	static AARectangle Inset(const AARectangle& rect, Vec2D& insets);

	virtual std::vector<Vec2D> GetPoints() const override;
};

#endif /*SHAPES_AARECTANGLE_H_*/
