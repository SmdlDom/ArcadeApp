#include "Circle.h"
#include "Utils.h"

Circle::Circle(): Circle(Vec2D::Zero,0) {}

Circle::Circle(const Vec2D& center, float radius): _radius(radius) {
	_points.push_back(center);
}

bool Circle::Intersect(const Circle& otherCircle) const {
	return GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (_radius + otherCircle._radius);
}

bool Circle::ContainsPoint(const Vec2D& point) const {
	return IsLE(GetCenterPoint().Distance(point), _radius);
}
