#pragma once

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "CustomHelper.h"


std::string FONT_DIR = "Resources/Fonts/";
std::string ARIAL = FONT_DIR + "Arial/arial.ttf";

std::string DEFAULT_FONT = ARIAL;
int DEFAULT_FONT_SIZE = 20;
SDL_Color DEFAULT_FONT_COLOR = SDL_COLOR_WHITE;


class CustomText {

private:
	TTF_Font* _font;
	SDL_Surface* _textSurface;
	SDL_Texture* _textTexture;
	SDL_Rect _textRect;
	SDL_Renderer* _rendererContext;

	std::string _text;
	std::string _fontName;
	int _fontSize;
	SDL_Color _fontColor;
	int _x, _y;

	void openFont() {
		_font = TTF_OpenFont(_fontName.c_str(), _fontSize);
		if (_font == NULL) {
			std::cerr << "Error TTF_OpenFont in CustomText::renderText()" << std::endl;
			return;
		}
	}

public:
	CustomText(SDL_Renderer* rendererContext, std::string text, int fontSize, SDL_Color fontColor, std::string fontName, int x, int y) :
		_rendererContext{ rendererContext }, _text{ text }, _fontSize{ fontSize }, _fontColor{ fontColor }, 
		_fontName{ fontName }, _x{ x }, _y{ y } { 

		TTF_Init();
		openFont();
	}

	CustomText() :
		CustomText(NULL, "", DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, DEFAULT_FONT, 0, 0) {}

	CustomText(SDL_Renderer* rendererContext, std::string text) :
		CustomText(rendererContext, text, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, DEFAULT_FONT, 0, 0) {}

	CustomText(SDL_Renderer* rendererContext, std::string text, int fontSize) :
		CustomText(rendererContext, text, fontSize, DEFAULT_FONT_COLOR, DEFAULT_FONT, 0, 0) {}

	CustomText(SDL_Renderer* rendererContext, std::string text, SDL_Color fontColor) :
		CustomText(rendererContext, text, DEFAULT_FONT_SIZE, fontColor, DEFAULT_FONT, 0, 0) {}

	CustomText(SDL_Renderer* rendererContext, std::string text, std::string fontName) :
		CustomText(rendererContext, text, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, fontName, 0, 0) {}

	CustomText(SDL_Renderer* rendererContext, std::string text, int x, int y) :
		CustomText(rendererContext, text, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, DEFAULT_FONT, x, y) {}

	CustomText(SDL_Renderer* rendererContext, std::string text, int fontSize, SDL_Color fontColor) :
		CustomText(rendererContext, text, fontSize, fontColor, ARIAL, 0, 0) {}

	CustomText(SDL_Renderer* rendererContext, std::string text, int fontSize, SDL_Color fontColor, std::string fontName) :
		CustomText(rendererContext, text, fontSize, fontColor, fontName, 0, 0) {}


	void setText(std::string text) {
		_text = text;
	}
	void setFontName(std::string fontName) {
		_fontName = fontName;
		openFont();
	}
	void setFontSize(int fontSize) {
		_fontSize = fontSize;
		openFont();
	}
	void setFontColor(SDL_Color fontColor) {
		_fontColor = fontColor;
	}
	void setX(int x) {
		_x = x;
	}
	void setY(int y) {
		_y = y;
	}
	void setRendererContext(SDL_Renderer* rendererContext) {
		_rendererContext = rendererContext;
	}
	


	std::string getText() {
		return _text;
	}
	std::string getFontName() {
		return _fontName;
	}
	int getFontSize() {
		return _fontSize;
	}
	SDL_Color getFontColor() {
		return _fontColor;
	}
	int getX() {
		return _x;
	}
	int getY() {
		return _y;
	}
	SDL_Renderer* getRendererContext() {
		return _rendererContext;
	}
	SDL_Rect getRect() {
		return _textRect;
	}
	SDL_Texture* getTexture() {
		return _textTexture;
	}


	void renderText() {

		if (_text.empty())
			_text = " ";

		_textSurface = TTF_RenderText_Solid(_font, _text.c_str(), _fontColor);
		if (_textSurface == NULL) {
			std::cerr << "Error TTF_RenderText_Solid in CustomText::renderText()" << std::endl;
			return;
		}

		_textTexture = SDL_CreateTextureFromSurface(_rendererContext, _textSurface);
		if (_textTexture == NULL) {
			std::cerr << "Error SDL_CreateTextureFromSurface in CustomText::renderText()" << std::endl;
			return;
		}

		_textRect = { _x, _y, _textSurface->w, _textSurface->h };
	}


	void setCenteredHorizontally(const int& windowWidth, const int& windowHeight) {
		_x = windowWidth/2 - _textRect.w/2;
	}
	void setCenteredVertically(const int& windowWidth, const int& windowHeight) {
		_y = windowHeight/2 - _textRect.h/2;
	}
	void setCentered(const int& windowWidth, const int& windowHeight) {
		setCenteredVertically(windowWidth, windowHeight);
		setCenteredHorizontally(windowWidth, windowHeight);
	}

};