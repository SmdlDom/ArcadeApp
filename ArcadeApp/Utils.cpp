#include "Utils.h"

#include <cmath>

bool IsEqual(float x, float y) {
	return fabsf(x - y) < EPSILON;
}

bool IsGE(float x, float y) {
	return x > y || IsEqual(x, y);
}

bool IsLE(float x, float y) {
	return x < y || IsEqual(x, y);
}