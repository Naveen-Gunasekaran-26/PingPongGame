#ifndef CUSTOM_TEXT_H
#define CUSTOM_TEXT_H


#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "CustomHelper.h"


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

	void openFont();

public:
	CustomText();
	CustomText(SDL_Renderer* rendererContext, const std::string& text);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const SDL_Color& fontColor);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const std::string& fontName);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& x, const int& y);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize, const SDL_Color& fontColor);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize,
		const SDL_Color& fontColor, const std::string& fontName);
	CustomText(SDL_Renderer* rendererContext, const std::string& text, const int& fontSize,
		const SDL_Color& fontColor, const std::string& fontName, const int& x, const int& y);


	void setText(const std::string& text);
	void setFontName(const std::string& fontName);
	void setFontSize(const int& fontSize);
	void setFontColor(const SDL_Color& fontColor);
	void setX(const int& x);
	void setY(const int& y);
	void setRendererContext(SDL_Renderer* rendererContext);
	


	std::string getText() const;
	std::string getFontName() const;
	int getFontSize() const;
	SDL_Color getFontColor() const;
	int getX() const;
	int getY() const;
	SDL_Renderer* getRendererContext() const;
	SDL_Rect getRect() const;
	SDL_Texture* getTexture() const;


	void renderText();


	void setCenteredHorizontally(const int& windowWidth, const int& windowHeight);
	void setCenteredVertically(const int& windowWidth, const int& windowHeight);
	void setCentered(const int& windowWidth, const int& windowHeight);

};


#endif // !CUSTOM_TEXT_H