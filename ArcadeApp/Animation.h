#pragma once

#ifndef GRAPHICS_ANIMATION_H_
#define GRAPHICS_ANIMATION_H_

#include "Vec2D.h"
#include "Color.h"
#include "Utils.h"
#include <string>
#include <vector>

struct AnimationFrame {
	std::string frame = "";
	std::string overlay = "";
	Color frameColor = Color::White();
	Color overlayColor = Color::White();
	Vec2D size;
	Vec2D offset = Vec2D::Zero;
	int frameColorSet = 0;
};

class Animation {
private:
	std::string _AnimationName; 
	std::string _spriteSheetName;
	std::string _overlay;
	std::vector<std::string> _frames;
	std::vector<Color> _frameColors;
	std::vector<Color> _overlayColors;
	std::vector<Vec2D> _frameOffsets;
	Vec2D _size;
	int _fps;

public:
	Animation();
	
	AnimationFrame GetAnimationFrame(uint32_t frameNum) const;

	static std::vector<Animation> LoadAnimations(const std::string& animationFilePath);

	void AddFrame(const std::string& frame) { _frames.push_back(frame); }
	void AddFrameColor(const Color& color) { _frameColors.push_back(color); }
	void AddOverlayFrameColor(const Color& color) { _overlayColors.push_back(color); }
	void AddFrameOffset(const Vec2D& offset) { _frameOffsets.push_back(offset); }

	void SetSpriteSheetName(const std::string& spriteSheetName) { _spriteSheetName = spriteSheetName; }
	const std::string& GetSpriteSheetName() const { return _spriteSheetName; }

	void SetName(const std::string& animationName) { _AnimationName = animationName; }
	const std::string& GetName() const { return _AnimationName; }

	void SetSize(const Vec2D& size) { _size = size; }
	Vec2D Size() const { return _size; }

	void SetFPS(int fps) { _fps = fps; }
	int FPS() const { return _fps; }

	void SetOverlay(const std::string& overlayName) { _overlay = overlayName; }
	const std::string& OverlayName() const { return _overlay; }

	size_t NumFrames() const { return _frames.size(); }
	size_t NumframeColors() const { return _frameColors.size(); }
	size_t NumOverlayColors() const { return _overlayColors.size(); }
	size_t NumFrameOffsets() const { return _frameOffsets.size(); }
};

#endif /* GRAPHICS_ANIMATION_H_*/