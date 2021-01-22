#pragma once

#ifndef GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_
#define GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_

#include "Block.h"
#include <vector>
#include <stdint.h>
class Screen;
class ball;
class AARectangle;

class BreakoutGameLevel {
private:
	static const int BLOCK_WIDTH = 16;
	static const int BLOCK_HEIGHT = 8;

	std::vector<Block> _blocks;

	void CreateDefaultLevel(const AARectangle& boundary);

public:
	BreakoutGameLevel();
	void Init(const AARectangle& boundary);
	void Load(const std::vector<Block>& blocks);
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);

	bool IsLevelComplet() const;
	static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string& filePath);
};

#endif /* GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_*/