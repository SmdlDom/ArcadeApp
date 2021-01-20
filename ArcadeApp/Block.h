#pragma once


#ifndef GAMES_BREAKOUT_BLOCK_H_
#define GAMES_BREAKOUT_BLOCK_H_

#include "Excluder.h"
#include "Color.h"

class Ball;
class Screen;
struct BoundaryEdge;

class Block : public Excluder {
public:
	static const int UNBREAKABLE = -1;

	Block();
	void Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);
	void Draw(Screen& screen);
	void Bounce(Ball& ball, const BoundaryEdge& edge);

	void ReduceHP();
	inline int GetHP() const { return _hp; }
	inline bool IsDestroyed() const { return _hp == 0; }
	inline const Color& GetOutlineColor() const { return _outlineColor; }
	inline const Color& GetFillColor() const { return _fillColor; }

private:
	Color _outlineColor;
	Color _fillColor;

	int _hp; //-1 means unbreakable

};

#endif /* GAMES_BREAKOUT_BLOCK_H_*/