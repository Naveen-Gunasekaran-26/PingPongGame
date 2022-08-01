#include "CustomText.h"
#include <iostream>


CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize,
	const SDL_Color& fontColor, const std::string& fontName, const int& x, const int& y) :
	_rendererContext{ rendererContext }, _text{ text }, _fontSize{ fontSize }, _fontColor{ fontColor },
	_fontName{ fontName }, _x{ x }, _y{ y } {

	TTF_Init();
	openFont();
}

CustomText::CustomText() :
	CustomText(NULL, "", DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, DEFAULT_FONT, 0, 0) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text) :
	CustomText(rendererContext, text, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, DEFAULT_FONT, 0, 0) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize) :
	CustomText(rendererContext, text, fontSize, DEFAULT_FONT_COLOR, DEFAULT_FONT, 0, 0) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const SDL_Color& fontColor) :
	CustomText(rendererContext, text, DEFAULT_FONT_SIZE, fontColor, DEFAULT_FONT, 0, 0) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const std::string& fontName) :
	CustomText(rendererContext, text, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, fontName, 0, 0) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& x, const int& y) :
	CustomText(rendererContext, text, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR, DEFAULT_FONT, x, y) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize, const SDL_Color& fontColor) :
	CustomText(rendererContext, text, fontSize, fontColor, ARIAL, 0, 0) {}

CustomText::CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize,
	const SDL_Color& fontColor, const std::string& fontName) :
	CustomText(rendererContext, text, fontSize, fontColor, fontName, 0, 0) {}


void CustomText::setText(const std::string& text) {
	_text = text;
}
void CustomText::setFontName(const std::string& fontName) {
	_fontName = fontName;
	openFont();
}
void CustomText::setFontSize(const int& fontSize) {
	_fontSize = fontSize;
	openFont();
}
void CustomText::setFontColor(const SDL_Color& fontColor) {
	_fontColor = fontColor;
}
void CustomText::setX(const int& x) {
	_x = x;
}
void CustomText::setY(const int& y) {
	_y = y;
}
void CustomText::setRendererContext(SDL_Renderer* rendererContext) {
	_rendererContext = rendererContext;
}



std::string CustomText::getText() const {
	return _text;
}
std::string CustomText::getFontName() const {
	return _fontName;
}
int CustomText::getFontSize() const {
	return _fontSize;
}
SDL_Color CustomText::getFontColor() const {
	return _fontColor;
}
int CustomText::getX() const {
	return _x;
}
int CustomText::getY() const {
	return _y;
}
SDL_Renderer* CustomText::getRendererContext() const {
	return _rendererContext;
}
SDL_Rect CustomText::getRect() const {
	return _textRect;
}
SDL_Texture* CustomText::getTexture() const {
	return _textTexture;
}


void CustomText::renderText() {

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


void CustomText::setCenteredHorizontally(const int& windowWidth, const int& windowHeight) {
	_x = windowWidth / 2 - _textRect.w / 2;
}
void CustomText::setCenteredVertically(const int& windowWidth, const int& windowHeight) {
	_y = windowHeight / 2 - _textRect.h / 2;
}
void CustomText::setCentered(const int& windowWidth, const int& windowHeight) {
	setCenteredVertically(windowWidth, windowHeight);
	setCenteredHorizontally(windowWidth, windowHeight);
}



// Private functions
void CustomText::openFont() {
	_font = TTF_OpenFont(_fontName.c_str(), _fontSize);
	if (_font == NULL) {
		std::cerr << "Error TTF_OpenFont in CustomText::renderText()" << std::endl;
		return;
	}
}