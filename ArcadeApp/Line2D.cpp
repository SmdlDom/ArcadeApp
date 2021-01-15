#include <cmath>

#include "Line2D.h"
#include "Utils.h"

Line2D::Line2D(): _p0(Vec2D::Zero), _p1(Vec2D::Zero) {}

Line2D::Line2D(float x0, float y0, float x1, float y1): Line2D(Vec2D(x0, y0), Vec2D(x1, y1)) {}

Line2D::Line2D(const Vec2D& p0, const Vec2D& p1): _p0(p0), _p1(p1) {}

bool Line2D::operator==(const Line2D& line) const {
	return line.GetP0() == _p0 && line.GetP1() == _p1;
}

float Line2D::MinDistanceFrom(const Vec2D& p, bool limitToSegment) const {
	return p.Distance(ClosestPoint(p, limitToSegment));
}

Vec2D Line2D::Midpoint() const {
	return Vec2D((_p0.GetX() + _p1.GetX()) / 2.0f, (_p0.GetY() + _p1.GetY()) / 2.0f);
}

Vec2D Line2D::ClosestPoint(const Vec2D& p, bool limitToSegment) const {
	Vec2D p0ToP = p - _p0;
	Vec2D p0ToP1 = _p1 - _p0;

	float l2 = p0ToP1.Mag2();
	float dot = p0ToP.Dot(p0ToP1);
	float t = dot / l2;

	if (limitToSegment) t = std::fmax(0, std::fmin(1.0f, t));

	return _p0 + p0ToP1 * t;
}

float Line2D::Slope() const {
	float dx = _p1.GetX() - _p0.GetX();
	if (fabsf(dx) < EPSILON) return 0;

	float dy = _p1.GetY() - _p0.GetY();
	return dy / dx;
}

float Line2D::Length() const {
	return _p1.Distance(_p0);
}
