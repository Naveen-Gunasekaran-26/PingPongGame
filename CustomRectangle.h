#ifndef CUSTOM_RECTANGLE_H
#define CUSTOM_RECTANGLE_H


#include "SDL.h"
#include "CustomHelper.h"


class CustomRectangle {

private:
	SDL_Rect _rect;
	float _velx, _vely;
	float _collisionTolerance;
	SDL_Color _color;
	SDL_BlendMode _colorBlendMode = SDL_BLENDMODE_BLEND;
	SDL_Renderer* _rendererContext;

public:
	CustomRectangle();
	CustomRectangle(SDL_Renderer* rendererContext);
	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h);
	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float collisionTolerance);
	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely);
	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely, float collisionTolerance);
	CustomRectangle(SDL_Renderer* rendererContext, const float& x, const float& y,
		const float& w, const float& h, const float& velx, const float& vely,
		const float& collisionTolerance, const SDL_Color& color);


	void setX(const float& x);
	void setY(const float& y);
	void setW(const float& w);
	void setH(const float& h);
	void setVelX(const float& velx);
	void setVelY(const float& vely);
	void setCollisionTolerance(const float& collisionTolerance);
	void setColor(const SDL_Color& color);
	void setColorBlendMode(const SDL_BlendMode& colorBlendMode);
	void setRendererContext(SDL_Renderer* rendererContext);
	void setRect(const SDL_Rect& rect);

	float getX() const;
	float getY() const;
	float getW() const;
	float getH() const;
	float getVelX() const;
	float getVelY() const;
	float getCollisionTolerance() const;
	SDL_Color setColor() const;
	SDL_BlendMode getColorBlendMode() const;
	SDL_Renderer* getRendererContext() const;
	SDL_Rect getRect() const;


	void renderRectangle();
	void setCenteredHorizontally(const int& windowWidth, const int& windowHeight);
	void setCenteredVertically(const int& windowWidth, const int& windowHeight);
	void setCentered(const int& windowWidth, const int& windowHeight);

	bool hasCollidedUp(const CustomRectangle& otherRect) const;
	bool hasCollidedDown(const CustomRectangle& otherRect) const;
	bool hasCollidedLeft(const CustomRectangle& otherRect) const;
	bool hasCollidedRight(const CustomRectangle& otherRect) const;
};


#endif // !CUSTOM_RECTANGLE_H