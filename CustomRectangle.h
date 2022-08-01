#pragma once

#include "SDL.h"
#include "CustomHelper.h"

SDL_Color DEFAULT_RECT_COLOR = SDL_COLOR_WHITE;


class CustomRectangle {

private:
	SDL_Rect _rect;
	float _velx, _vely;
	float _collisionTolerance;
	SDL_Color _color;
	SDL_BlendMode _colorBlendMode = SDL_BLENDMODE_BLEND;
	SDL_Renderer* _rendererContext;

public:
	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely,
		float collisionTolerance, SDL_Color color):
		_rendererContext{rendererContext}, _rect {(int)x, (int)y, (int)w, (int)h},
		_velx{ velx }, _vely{ vely },
		_collisionTolerance{ collisionTolerance }, _color{ color } {}
	
	CustomRectangle() :
		CustomRectangle(NULL, 0, 0, 0, 0, 0, 0, 0, DEFAULT_RECT_COLOR) {}

	CustomRectangle(SDL_Renderer* rendererContext) :
		CustomRectangle(rendererContext, 0, 0, 0, 0, 0, 0, 0, DEFAULT_RECT_COLOR) {}

	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h) :
		CustomRectangle(rendererContext, x, y, w, h, 0, 0, 0, DEFAULT_RECT_COLOR) {}

	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float collisionTolerance) :
		CustomRectangle(rendererContext, x, y, w, h, 0, 0, collisionTolerance, DEFAULT_RECT_COLOR) {}

	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely) :
		CustomRectangle(rendererContext, x, y, w, h, velx, vely, 0, DEFAULT_RECT_COLOR) {}

	CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely, float collisionTolerance) :
		CustomRectangle(rendererContext, x, y, w, h, velx, vely, collisionTolerance, DEFAULT_RECT_COLOR) {}


	void setX(const float& x) { _rect.x = (int)x; }
	void setY(const float& y) { _rect.y = (int)y; }
	void setW(const float& w) { _rect.w = (int)w; }
	void setH(const float& h) { _rect.h = (int)h; }
	void setVelX(const float& velx) { _velx = velx; }
	void setVelY(const float& vely) { _vely = vely; }
	void setCollisionTolerance(const float& collisionTolerance) { _collisionTolerance = collisionTolerance; }
	void setColor(const SDL_Color& color) { _color = color; }
	void setColorBlendMode(const SDL_BlendMode& colorBlendMode) { _colorBlendMode = colorBlendMode; }
	void setRendererContext(SDL_Renderer* rendererContext) { _rendererContext = rendererContext; }
	void setRect(const SDL_Rect& rect) { _rect = rect; }

	float getX() { return _rect.x; }
	float getY() { return _rect.y; }
	float getW() { return _rect.w; }
	float getH() { return _rect.h; }
	float getVelX() { return _velx; }
	float getVelY() { return _vely; }
	float getCollisionTolerance() { return _collisionTolerance; }
	SDL_Color setColor() { return _color; }
	SDL_BlendMode getColorBlendMode() { return _colorBlendMode; }
	SDL_Renderer* getRendererContext() { return _rendererContext; }
	SDL_Rect getRect() { return _rect; }


	void renderRectangle() {
		SDL_SetRenderDrawColor(_rendererContext, _color.r, _color.g, _color.b, _color.a);
		SDL_SetRenderDrawBlendMode(_rendererContext, _colorBlendMode);
	}

	void setCenteredHorizontally(const int& windowWidth, const int& windowHeight) {
		_rect.x = windowWidth / 2 - _rect.w / 2;
	}
	void setCenteredVertically(const int& windowWidth, const int& windowHeight) {
		_rect.y = windowHeight / 2 - _rect.h / 2;
	}
	void setCentered(const int& windowWidth, const int& windowHeight) {
		setCenteredVertically(windowWidth, windowHeight);
		setCenteredHorizontally(windowWidth, windowHeight);
	}

	bool hasCollidedUp(CustomRectangle otherRect) {
		if (
			(otherRect.getVelY() > 0) &&
			( inBetween(otherRect.getX(), _rect.x, _rect.x + _rect.w) || 
			  inBetween(otherRect.getX() + otherRect.getW(), _rect.x, _rect.x + _rect.w) ) &&
			  ( abs(otherRect.getY()+otherRect.getH()-_rect.y) < otherRect.getCollisionTolerance() + _collisionTolerance)
			)
			return true;
		return false;
	}

	bool hasCollidedDown(CustomRectangle otherRect) {
		if (
			(otherRect.getVelY() < 0) &&
			(inBetween(otherRect.getX(), _rect.x, _rect.x + _rect.w) ||
				inBetween(otherRect.getX() + otherRect.getW(), _rect.x, _rect.x + _rect.w)) &&
			(abs(otherRect.getY() - (_rect.y+_rect.h)) < otherRect.getCollisionTolerance() + _collisionTolerance)
			)
			return true;
		return false;
	}

	bool hasCollidedLeft(CustomRectangle otherRect) {
		if (
			(otherRect.getVelX() > 0) &&
			(inBetween(otherRect.getY(), _rect.y, _rect.y + _rect.h) ||
				inBetween(otherRect.getY() + otherRect.getH(), _rect.y, _rect.y + _rect.h)) &&
			(abs(otherRect.getX()+ otherRect.getW() - _rect.x) < otherRect.getCollisionTolerance() + _collisionTolerance)
			)
			return true;
		return false;
	}

	bool hasCollidedRight(CustomRectangle otherRect) {
		if (
			(otherRect.getVelX() < 0) &&
			(inBetween(otherRect.getY(), _rect.y, _rect.y + _rect.h) ||
				inBetween(otherRect.getY() + otherRect.getH(), _rect.y, _rect.y + _rect.h)) &&
			(abs(otherRect.getX() - (_rect.x + _rect.w)) < otherRect.getCollisionTolerance() + _collisionTolerance)
			)
			return true;
		return false;
	}
};