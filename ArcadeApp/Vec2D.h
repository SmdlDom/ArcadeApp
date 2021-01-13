#pragma once

#ifndef UTILS_VEC2D_H_
#define UTILS_VEC2D_H_

#include <iostream>

class Vec2D {
	private:
	float _x, _y;

	public:

	static const Vec2D Zero;

	Vec2D() : Vec2D(0, 0) {}
	Vec2D(float x, float y) : _x(x), _y(y) {}

	inline void SetX(float x) { _x = x; }
	inline void SetY(float y) { _y = y; }
	inline float GetX() const { return _x; }
	inline float GetY() const { return _y; }

	friend std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec);
	
	//Boolean operation
	bool operator==(const Vec2D& vec2) const;
	bool operator!=(const Vec2D& vec2) const;

	//One vector operation
	Vec2D operator-() const;
	Vec2D operator*(float scale) const;
	Vec2D operator/(float scale) const;
	Vec2D& operator*=(float scale);
	Vec2D& operator/=(float scale);

	friend Vec2D operator*(float scalar, const Vec2D& vec);

	//Two vector operation
	Vec2D operator+(const Vec2D& vec) const;
	Vec2D operator-(const Vec2D& vec) const;
	Vec2D& operator+=(const Vec2D& vec);
	Vec2D& operator-=(const Vec2D& vec);

	float Mag2() const;
	float Mag() const;

	Vec2D GetUnitVec() const;
	Vec2D& Normalize();

	float Distance(const Vec2D& vec) const;
	float Dot(const Vec2D& vec) const;

	Vec2D ProjectOnto(const Vec2D& vec2) const;

	float AngleBetween(const Vec2D& vec2) const;

	Vec2D Reflect(const Vec2D& normal) const;

	Vec2D RotationResult(float angle, const Vec2D& aroundPoint) const;
	void Rotate(float angle, const Vec2D& aroundPoint);
	
};
 

#endif /* UTILS_VEC2D_H_*/


