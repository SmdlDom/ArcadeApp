#include "Vec2D.h"
#include "Utils.h"
#include <cassert>
#include <cmath>

const Vec2D Vec2D::Zero;

//Definition of friend methods
std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec) {
	std::cout << "X: " << vec._x << ", Y: " << vec._y << std::endl;
	return consoleOut;
}

Vec2D operator*(float scalar, const Vec2D& vec) {
	return vec * scalar;
}

Vec2D operator/(float scalar, const Vec2D& vec) {
	return Vec2D();
}

//Definition of other method
bool Vec2D::operator==(const Vec2D& vec2) const {
	return IsEqual(_x, vec2._x) && IsEqual(_y, vec2._y);
}

bool Vec2D::operator!=(const Vec2D& vec2) const {
	return !(*this == vec2);
}

Vec2D Vec2D::operator-() const {
	return Vec2D(-_x, -_y);
}

Vec2D Vec2D::operator*(float scale) const {
	return Vec2D(scale * _x, scale * _y);
}

Vec2D Vec2D::operator/(float scale) const {
	assert(fabsf(scale > EPSILON));
	return Vec2D(_x / scale, _y / scale);
}

Vec2D& Vec2D::operator*=(float scale) {
	*this = *this * scale;
	return *this;
}

Vec2D& Vec2D::operator/=(float scale) {
	assert(fabsf(scale) > EPSILON);
	*this = *this / scale;
	return *this;
}

Vec2D Vec2D::operator+(const Vec2D& vec) const {
	return Vec2D(_x + vec._x, _y + vec._y);
}

Vec2D Vec2D::operator-(const Vec2D& vec) const {
	return Vec2D(_x - vec._x, _y - vec._y);
}

Vec2D& Vec2D::operator+=(const Vec2D& vec) {
	*this = *this + vec;
	return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& vec) {
	*this = *this + vec;
	return *this;
}

float Vec2D::Mag2() const {
	return Dot(*this);
}

float Vec2D::Mag() const {
	return sqrt(Mag2());
}

Vec2D Vec2D::GetUnitVec() const {
	float mag = Mag();
	if (mag > EPSILON) {
		return *this / mag;
	} else {
		return Vec2D::Zero;
	}
}

Vec2D& Vec2D::Normalize() {
	*this = GetUnitVec();
	return *this;
}

float Vec2D::Distance(const Vec2D& vec) const {
	return (vec - *this).Mag();
}

float Vec2D::Dot(const Vec2D& vec) const {
	return _x * vec._x + _y * vec._y;
}

Vec2D Vec2D::ProjectOnto(const Vec2D& vec2) const {
	float mag2 = vec2.Mag2();

	if (IsLE(mag2, EPSILON)) {
		return Vec2D::Zero;
	}

	float dot = Dot(vec2);
	return vec2 * (dot / mag2);
}

float Vec2D::AngleBetween(const Vec2D& vec2) const {
	return acosf(GetUnitVec().Dot(vec2.GetUnitVec()));
}

Vec2D Vec2D::Reflect(const Vec2D& normal) const {
	return *this - 2 * ProjectOnto(normal);
}

Vec2D Vec2D::RotationResult(float angle, const Vec2D& aroundPoint) const {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Vec2D thisVec(_x, _y);
	thisVec -= aroundPoint;

	float xRot = thisVec._x * cos - thisVec._y * sin;
	float yRot = thisVec._x * sin + thisVec._y * cos;

	Vec2D rot = Vec2D(xRot, yRot);

	return rot + aroundPoint;
}

void Vec2D::Rotate(float angle, const Vec2D& aroundPoint) {
	*this = RotationResult(angle, aroundPoint);
}

