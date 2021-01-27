#include "AnimatedSprite.h"
#include "AARectangle.h"
#include "Screen.h"

AnimatedSprite::AnimatedSprite():_position(Vec2D::Zero), _noptrSpriteSheet(nullptr) {}

void AnimatedSprite::Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color) {
	_animationPlayer.Init(animationsPath);
	_noptrSpriteSheet = &spriteSheet;
	_color = color;
}

void AnimatedSprite::Update(uint32_t dt) {
	_animationPlayer.Update(dt);
}

void AnimatedSprite::Draw(Screen& theScreen) {
	AnimationFrame frame = _animationPlayer.GetCurrentAnimationFrame();

	Color frameColor = frame.frameColor;

	if (!frame.frameColorSet) frameColor = _color;

	theScreen.Draw(*_noptrSpriteSheet, frame.frame, _position + frame.offset, frameColor);

	if (frame.overlay.size() > 0) {
		theScreen.Draw(*_noptrSpriteSheet, frame.overlay, _position, frame.overlayColor);
	}
}

void AnimatedSprite::SetAnimation(const std::string& animationName, bool looped) {
	_animationPlayer.Play(animationName, looped);
}

Vec2D AnimatedSprite::Size() const {
	return _animationPlayer.GetCurrentAnimationFrame().size;
}

void AnimatedSprite::Stop() {
	_animationPlayer.Stop();
}

const AARectangle AnimatedSprite::GetBoundingBox() const {
	AARectangle bbox = { _position, static_cast<unsigned int>(Size().GetX()), static_cast<unsigned int>(Size().GetY()) };
	return bbox;
}
