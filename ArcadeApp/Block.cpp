#include "Block.h"
#include "Screen.h"
#include "Ball.h"

Block::Block(): _outlineColor(Color::White()), _fillColor(Color::White()), _hp(1) {}

void Block::Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor) {
	Excluder::Init(rect);
	_hp = hp;
	_outlineColor = outlineColor;
	_fillColor = fillColor;
}

void Block::Draw(Screen& screen) {
	screen.Draw(GetAARectangle(), _outlineColor, true, _fillColor);
}

void Block::Bounce(Ball& ball, const BoundaryEdge& edge) {
	ball.Bounce(edge);
}


void Block::ReduceHP() {
	if (_hp > 0) --_hp;
}
