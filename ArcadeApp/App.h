#pragma once

#ifndef APP_APP_H_
#define APP_APP_H_

#include <stdint.h>
#include <vector>
#include <memory>
#include "Screen.h"
#include "Scene.h"
#include "InputController.h"
#include "BitmapFont.h"

struct SDL_Window;

class App {
private:
	Screen _screen;
	SDL_Window* mnoptrWindow;

	std::vector<std::unique_ptr<Scene>> _sceneStack;
	InputController _inputController;

	BitmapFont _font;

public: 
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();

	inline uint32_t Width() const { return _screen.Width(); }
	inline uint32_t Height() const { return _screen.Height(); }
	inline const BitmapFont& GetFont() const { return _font; }

	void PushScene(std::unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene();

	static const std::string& GetBasePath();

	
};

#endif /* APP_APP_H_*/