#pragma once


#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <string>

static const float EPSILON = 0.0001f;

const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;

struct Size {
	unsigned int width = 0, height = 0;
};

bool IsEqual(float x, float y);

bool IsGE(float x, float y);

bool IsLE(float x, float y);

float Clamp(float val, float min, float max);

float MillisecondsToSeconds(unsigned int milliseconds);

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c);

bool StringCompare(const std::string& a, const std::string& b);



#endif /*UTILS_UTILS_H_*/

class Utils {};

