// ArcadeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#undef main

#include <iostream>

#include "Color.h"
#include "Screen.h"

using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, const char * argv[]) {

	Screen screen;

	screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	screen.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::Yellow());
	screen.SwapScreens();

	//Event loop
	SDL_Event sdlEvent;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}
	}

	return 0;
}

