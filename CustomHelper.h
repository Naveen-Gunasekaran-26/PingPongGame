#ifndef CUSTOM_HELPER_H
#define CUSTOM_HELPER_H

#include <iostream>
#include <string>
#include "SDL.h"


const SDL_Color SDL_COLOR_WHITE = { 255, 255, 255, 255 };
const SDL_Color SDL_COLOR_BLACK = { 0, 0, 0, 255 };


const std::string FONT_DIR = "Resources/Fonts/";
const std::string ARIAL = FONT_DIR + "Arial/arial.ttf";

const std::string DEFAULT_FONT = ARIAL;
const int DEFAULT_FONT_SIZE = 20;
const SDL_Color DEFAULT_FONT_COLOR = SDL_COLOR_WHITE;
const SDL_Color DEFAULT_RECT_COLOR = SDL_COLOR_WHITE;



namespace CustomHelper {

	static bool inBetween(const float& x, const float& start, const float& end) {
		if (x >= std::min(start, end) && x <= std::max(start, end))
			return true;
		return false;
	}
}

#endif // !CUSTOM_HELPER_H
