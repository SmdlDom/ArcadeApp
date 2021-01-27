#pragma once

#ifndef GRAPHICS_ANIMATIONPLAYER_H_
#define GRAPHICS_ANIMATIONPLAYER_H_

#include "Animation.h"
#include <stdint.h>
#include <vector>
#include <string>

class AnimationPlayer {
private:
	uint32_t _time;
	std::vector<Animation> _animations;
	size_t _currentAnimation;
	uint32_t _frame;

	bool _looped;
	bool _isPlaying;
	bool _isFinishedPlaying;

public:
	AnimationPlayer();
	bool Init(const std::string& animationsPath);
	bool Play(const std::string& animationName, bool looped);
	void Pause();
	void Stop();
	void Update(uint32_t dt);
	AnimationFrame GetCurrentAnimationFrame() const;

	inline bool IsFinishedPlaying() const { return _isFinishedPlaying; }
	inline uint32_t GetCurrentFrameNumber() const { return _frame; }
};

#endif /* GRAPHICS_ANIMATIONPLAYER_H_*/