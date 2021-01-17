#include "AARectangle.h"
#include "Utils.h"
#include <cmath>

AARectangle::AARectangle(): AARectangle(Vec2D::Zero, Vec2D::Zero) {}

AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height) {
	_points.push_back(topLeft);
	_points.push_back(Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight) {
	_points.push_back(topLeft);
	_points.push_back(bottomRight);
}

float AARectangle::GetWidth() const {
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}

float AARectangle::GetHeight() const {
	return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY() + 1;
}

void AARectangle::MoveTo(const Vec2D& position) {
	float width = GetWidth();
	float height = GetHeight();

	SetTopLeftPoint(position);
	SetBottomRightPoint(Vec2D(position.GetX() + width - 1, position.GetY() + height - 1));
}

Vec2D AARectangle::GetCenterPoint() const {
	return Vec2D(GetTopLeftPoint().GetX() + GetWidth()/2.0f, GetTopLeftPoint().GetY() + GetHeight()/2.0f);
}

bool AARectangle::Intersect(const AARectangle& otherRect) const {
	return !(otherRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() ||
			 otherRect.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY() ||
			 otherRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX() ||
			 otherRect.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY());
}

bool AARectangle::ContainsPoint(const Vec2D& point) const {
	bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
	bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY();

	return withinX && withinY;
}

AARectangle AARectangle::Inset(const AARectangle& rect, Vec2D& insets) {
	return AARectangle(rect.GetTopLeftPoint() + insets,
					   rect.GetWidth() - 2*insets.GetX(),
					   rect.GetHeight() - 2*insets.GetY());
}

std::vector<Vec2D> AARectangle::GetPoints() const {
	std::vector<Vec2D> points;

	points.push_back(_points[0]);
	points.push_back(Vec2D(_points[1].GetX(), _points[0].GetY()));
	points.push_back(_points[1]);
	points.push_back(Vec2D(_points[0].GetX(), _points[1].GetY()));

	return points;
}

