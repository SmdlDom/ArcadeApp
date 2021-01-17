// ArcadeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#undef main

#include <iostream>

#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"

using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 4;

int main(int argc, const char * argv[]) {

	Screen screen;

	screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Line2D line = { Vec2D(0,0), Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT) };
	Triangle triangle = { Vec2D(60,10), Vec2D(10,110), Vec2D(110,110) };
	AARectangle rect = { Vec2D(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25), 50, 50 };
	Circle circle = { Vec2D(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50), 50};

	screen.Draw(circle, Color(255, 0, 0, 150), true, Color(255, 0, 0, 150));
	screen.Draw(rect, Color(0,255,0,150), true, Color(0,255,0,150));
	screen.Draw(triangle, Color::Red(), true, Color::Red());
	screen.Draw(line, Color::White());
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

