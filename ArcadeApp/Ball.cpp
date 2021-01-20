#include "Ball.h"
#include "Utils.h"
#include "Screen.h"
#include "Circle.h"
#include "BoundaryEdge.h"

const float Ball::RADIUS = 4.0f;

Ball::Ball(): Ball(Vec2D::Zero, RADIUS) {}

Ball::Ball(const Vec2D& pos, float radius) : _bBox(pos - Vec2D(radius, radius), radius * 2.0f - 0.5f, radius * 2.0f - 0.5f), _velocity(Vec2D::Zero) {}

void Ball::Update(uint32_t dt) {
	_bBox.MoveBy(_velocity * MillisecondsToSeconds(dt));
}

void Ball::Draw(Screen& screen) {
	Circle circ = { _bBox.GetCenterPoint(), GetRadius() };
	screen.Draw(circ, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge) {
	if (edge.normal == DOWN_DIR) {
		_bBox.MoveTo(Vec2D(_bBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
	} else if (edge.normal == UP_DIR) {
		_bBox.MoveTo(Vec2D(_bBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - _bBox.GetHeight()));
	} else if (edge.normal == RIGHT_DIR) {
		_bBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), _bBox.GetTopLeftPoint().GetY()));
	} else if (edge.normal == LEFT_DIR) {
		_bBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() - _bBox.GetWidth(), _bBox.GetTopLeftPoint().GetY()));
	}

	pointOnEdge = edge.edge.ClosestPoint(_bBox.GetCenterPoint(), limitToEdge);
}

void Ball::MoveTo(const Vec2D& point) {
	_bBox.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
}

void Ball::Bounce(const BoundaryEdge& edge) {
	Vec2D pointOnEdge;

	MakeFlushWithEdge(edge, pointOnEdge, false);
	_velocity = _velocity.Reflect(edge.normal);
}

