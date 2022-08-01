#pragma once

#include "SDL.h"

SDL_Color SDL_COLOR_WHITE = { 255, 255, 255, 255 };
SDL_Color SDL_COLOR_BLACK = { 0, 0, 0, 255 };

static bool inBetween(const float& x, const float& start, const float& end);

static bool inBetween(const float& x, const float& start, const float& end) {
	if (x >= std::min(start, end) && x <= std::max(start, end))
		return true;
	return false;
}