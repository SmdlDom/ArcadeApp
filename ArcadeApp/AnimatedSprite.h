#pragma once

#ifndef GRAPHICS_ANIMATEDSPRITE_H_
#define GRAPHICS_ANIMATEDSPRITE_H_

#include "AnimationPlayer.h"
#include "Vec2D.h"
#include "Color.h"
#include <stdint.h>
#include <string>

class AARectangle;
class Screen;
class SpriteSheet;

class AnimatedSprite {
private:
	const SpriteSheet* _noptrSpriteSheet;
	AnimationPlayer _animationPlayer;
	Vec2D _position;
	Color _color;
public:
	AnimatedSprite();
	void Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color = Color::White());
	void Update(uint32_t dt);
	void Draw(Screen& theScreen);

	void SetAnimation(const std::string& animationName, bool looped);
	Vec2D Size() const;
	void Stop();
	const AARectangle GetBoundingBox() const;

	inline Vec2D Position() const { return _position; }
	inline void SetPosition(const Vec2D& position) { _position = position; }
	inline void MoveBy(const Vec2D& delta) { _position += delta; }
	inline bool IsFinishedPlayingAnimation() const { return _animationPlayer.IsFinishedPlaying(); }
	inline const Color& GetColor() const { return _color; }
	const SpriteSheet* GetSpriteSheet() const { return _noptrSpriteSheet; }
};


#endif /* GRAPHICS_ANIMATEDSPRITE_H_*/