#include "Triangle.h"
#include "Utils.h"
#include <cmath>


float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const {
	return fabsf((p0.GetX() * (p1.GetY() - p2.GetY()) +
				  p1.GetX() * (p2.GetY() - p0.GetY()) +
				  p2.GetX() * (p0.GetY() - p1.GetY())) / 2.0f);
}

Triangle::Triangle():Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero) {}

Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) {
	_points.push_back(p0);
	_points.push_back(p1);
	_points.push_back(p2);
}

Vec2D Triangle::GetCenterPoint() const {
	float x = 0, y = 0;
	for (int i = 0; i < 3; i++) {
		x += _points[i].GetX();
		y += _points[i].GetY();
	}
	x /= 3.0f;
	y /= 3.0f;

	return Vec2D(x, y);
}

float Triangle::Area() const {
	return Area(GetP0(), GetP1(), GetP2());
}

bool Triangle::ContainsPoint(const Vec2D& p) const {
	float thisArea = Area();

	float a0 = Area(p, GetP1(), GetP2());
	float a1 = Area(GetP0(), p, GetP2());
	float a2 = Area(GetP0(), GetP1(), p);
	
	return IsEqual(thisArea, a0 + a1 + a2);
}
