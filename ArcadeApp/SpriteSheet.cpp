#include "SpriteSheet.h"
#include "FileCommandLoader.h"
#include "Utils.h"
#include "App.h"

bool SpriteSheet::LoadSpriteSections(const std::string& path) {
	FileCommandLoader fileLoader;

	Command spriteCommand;
	spriteCommand.command = "sprite";

	spriteCommand.parseFunc = [&](ParseFuncParams params) {
		BMPImageSection section;
		_sections.push_back(section);
	};
	fileLoader.AddCommand(spriteCommand);

	Command keyCommand;
	keyCommand.command = "key";

	keyCommand.parseFunc = [&](ParseFuncParams params) {
		_sections.back().key = FileCommandLoader::ReadString(params);
	};
	fileLoader.AddCommand(keyCommand);

	Command xPosCommand;
	xPosCommand.command = "xPos";

	xPosCommand.parseFunc = [&](ParseFuncParams params) {
		_sections.back().sprite.xPos = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(xPosCommand);

	Command yPosCommand;
	yPosCommand.command = "yPos";

	yPosCommand.parseFunc = [&](ParseFuncParams params) {
		_sections.back().sprite.yPos = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(yPosCommand);

	Command widthCommand;
	widthCommand.command = "width";

	widthCommand.parseFunc = [&](ParseFuncParams params) {
		_sections.back().sprite.width = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(widthCommand);

	Command heightCommand;
	heightCommand.command = "height";

	heightCommand.parseFunc = [&](ParseFuncParams params) {
		_sections.back().sprite.height = FileCommandLoader::ReadInt(params);
	};
	fileLoader.AddCommand(heightCommand);

	return fileLoader.LoadFile(path);
}

SpriteSheet::SpriteSheet() {}

bool SpriteSheet::Load(const std::string& name) {
	bool loadedImage = _BMPImage.Load(App::Singleton().GetBasePath() + std::string("Assets/") + name + ".bmp");
	bool loadedSpriteSections = LoadSpriteSections(App::Singleton().GetBasePath() + std::string("Assets/") + name + ".txt");

	return loadedImage && loadedSpriteSections;
}

Sprite SpriteSheet::GetSprite(const std::string& spriteName) const {
	size_t length = _sections.size();

	for (size_t i = 0; i < length; ++i) {
		if (StringCompare(_sections[i].key, spriteName)) return _sections[i].sprite;
	}

	return Sprite();
}

std::vector<std::string> SpriteSheet::SpriteNames() const {
	std::vector<std::string> spriteNames;

	for (const auto& section : _sections) {
		spriteNames.push_back(section.key);
	}

	return spriteNames;
}
