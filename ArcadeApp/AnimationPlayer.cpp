#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(): 
	_time(0), _currentAnimation(0), _frame(0), _looped(false), _isPlaying(false), _isFinishedPlaying(false) {}

bool AnimationPlayer::Init(const std::string& animationsPath) {
	_animations = Animation::LoadAnimations(animationsPath);
	return _animations.size() > 0;
}

bool AnimationPlayer::Play(const std::string& animationName, bool looped) {
	bool found = false;
	
	for (size_t i = 0; i < _animations.size(); ++i) {
		if (_animations[i].GetName() == animationName) {
			_currentAnimation = i;
			found = true;
			break;
		}
	}

	if (found) {
		_isPlaying = true;
		_frame = 0;
		_time = 0;
		_looped = looped;
		_isFinishedPlaying = false;
	}

	return found;
}

void AnimationPlayer::Pause() {
	if (_isFinishedPlaying) _isPlaying = !_isPlaying;
}

void AnimationPlayer::Stop() {
	_isPlaying = false;
	_time = 0;
	_frame = 0;
	_isFinishedPlaying = true;
}

void AnimationPlayer::Update(uint32_t dt) {
	if (_isPlaying) {
		_time += dt;

		int fps = _animations[_currentAnimation].FPS();
		float millisecondsPerFrame = static_cast<float>(1000) / static_cast<float>(fps);

		if (static_cast<float>(_time) > millisecondsPerFrame) {
			_time -= static_cast<uint32_t>(millisecondsPerFrame);
			if (_frame + 1 < _animations[_currentAnimation].NumFrames()) {
				++_frame;
			} else if ((_frame + 1 >= _animations[_currentAnimation].NumFrames()) && _looped) {
				_frame = 0;
			} else {
				_isFinishedPlaying = true;
			}
		}
	}
}

AnimationFrame AnimationPlayer::GetCurrentAnimationFrame() const {
	if (_animations.empty()) return AnimationFrame();
	return _animations[_currentAnimation].GetAnimationFrame(GetCurrentFrameNumber());
}
