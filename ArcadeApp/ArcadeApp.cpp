// ArcadeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#undef main

#include <iostream>
#include "App.h"

using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 4;

int main(int argc, const char * argv[]) {

	if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION)) {
		App::Singleton().Run();
	}


	return 0;
}

