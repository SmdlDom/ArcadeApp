#include "Shape.h"

void Shape::MoveBy(const Vec2D& deltaOffset) {
	for (Vec2D& point : _points) {
		point = point + deltaOffset;
	}
}
