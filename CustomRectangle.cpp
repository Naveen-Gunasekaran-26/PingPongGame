#include "CustomRectangle.h"
#include <iostream>


CustomRectangle::CustomRectangle(SDL_Renderer* rendererContext, const float& x, const float& y,
	const float& w, const float& h, const float& velx, const float& vely,
	const float& collisionTolerance, const SDL_Color& color) :
	_rendererContext{ rendererContext }, _rect{ (int)x, (int)y, (int)w, (int)h },
	_velx{ velx }, _vely{ vely },
	_collisionTolerance{ collisionTolerance }, _color{ color } {}

CustomRectangle::CustomRectangle() :
	CustomRectangle(NULL, 0, 0, 0, 0, 0, 0, 0, DEFAULT_RECT_COLOR) {}

CustomRectangle::CustomRectangle(SDL_Renderer* rendererContext) :
	CustomRectangle(rendererContext, 0, 0, 0, 0, 0, 0, 0, DEFAULT_RECT_COLOR) {}

CustomRectangle::CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h) :
	CustomRectangle(rendererContext, x, y, w, h, 0, 0, 0, DEFAULT_RECT_COLOR) {}

CustomRectangle::CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float collisionTolerance) :
	CustomRectangle(rendererContext, x, y, w, h, 0, 0, collisionTolerance, DEFAULT_RECT_COLOR) {}

CustomRectangle::CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely) :
	CustomRectangle(rendererContext, x, y, w, h, velx, vely, 0, DEFAULT_RECT_COLOR) {}

CustomRectangle::CustomRectangle(SDL_Renderer* rendererContext, float x, float y, float w, float h, float velx, float vely, float collisionTolerance) :
	CustomRectangle(rendererContext, x, y, w, h, velx, vely, collisionTolerance, DEFAULT_RECT_COLOR) {}


void CustomRectangle::setX(const float& x) { _rect.x = (int)x; }
void CustomRectangle::setY(const float& y) { _rect.y = (int)y; }
void CustomRectangle::setW(const float& w) { _rect.w = (int)w; }
void CustomRectangle::setH(const float& h) { _rect.h = (int)h; }
void CustomRectangle::setVelX(const float& velx) { _velx = velx; }
void CustomRectangle::setVelY(const float& vely) { _vely = vely; }
void CustomRectangle::setCollisionTolerance(const float& collisionTolerance) { _collisionTolerance = collisionTolerance; }
void CustomRectangle::setColor(const SDL_Color& color) { _color = color; }
void CustomRectangle::setColorBlendMode(const SDL_BlendMode& colorBlendMode) { _colorBlendMode = colorBlendMode; }
void CustomRectangle::setRendererContext(SDL_Renderer* rendererContext) { _rendererContext = rendererContext; }
void CustomRectangle::setRect(const SDL_Rect& rect) { _rect = rect; }

float CustomRectangle::getX() const { return _rect.x; }
float CustomRectangle::getY() const { return _rect.y; }
float CustomRectangle::getW() const { return _rect.w; }
float CustomRectangle::getH() const { return _rect.h; }
float CustomRectangle::getVelX() const { return _velx; }
float CustomRectangle::getVelY() const { return _vely; }
float CustomRectangle::getCollisionTolerance() const { return _collisionTolerance; }
SDL_Color CustomRectangle::setColor() const { return _color; }
SDL_BlendMode CustomRectangle::getColorBlendMode() const { return _colorBlendMode; }
SDL_Renderer* CustomRectangle::getRendererContext() const { return _rendererContext; }
SDL_Rect CustomRectangle::getRect() const { return _rect; }


void CustomRectangle::renderRectangle() {
	SDL_SetRenderDrawColor(_rendererContext, _color.r, _color.g, _color.b, _color.a);
	SDL_SetRenderDrawBlendMode(_rendererContext, _colorBlendMode);
}
void CustomRectangle::setCenteredHorizontally(const int& windowWidth, const int& windowHeight) {
	_rect.x = windowWidth / 2 - _rect.w / 2;
}
void CustomRectangle::setCenteredVertically(const int& windowWidth, const int& windowHeight) {
	_rect.y = windowHeight / 2 - _rect.h / 2;
}
void CustomRectangle::setCentered(const int& windowWidth, const int& windowHeight) {
	setCenteredVertically(windowWidth, windowHeight);
	setCenteredHorizontally(windowWidth, windowHeight);
}

bool CustomRectangle::hasCollidedUp(const CustomRectangle& otherRect) const {
	if (
		(otherRect.getVelY() > 0) &&
		(CustomHelper::inBetween(otherRect.getX(), _rect.x, _rect.x + _rect.w) ||
			CustomHelper::inBetween(otherRect.getX() + otherRect.getW(), _rect.x, _rect.x + _rect.w)) &&
		(abs(otherRect.getY() + otherRect.getH() - _rect.y) < otherRect.getCollisionTolerance() + _collisionTolerance)
		)
		return true;
	return false;
}

bool CustomRectangle::hasCollidedDown(const CustomRectangle& otherRect) const {
	if (
		(otherRect.getVelY() < 0) &&
		(CustomHelper::inBetween(otherRect.getX(), _rect.x, _rect.x + _rect.w) ||
			CustomHelper::inBetween(otherRect.getX() + otherRect.getW(), _rect.x, _rect.x + _rect.w)) &&
		(abs(otherRect.getY() - (_rect.y + _rect.h)) < otherRect.getCollisionTolerance() + _collisionTolerance)
		)
		return true;
	return false;
}

bool CustomRectangle::hasCollidedLeft(const CustomRectangle& otherRect) const {
	if (
		(otherRect.getVelX() > 0) &&
		(CustomHelper::inBetween(otherRect.getY(), _rect.y, _rect.y + _rect.h) ||
			CustomHelper::inBetween(otherRect.getY() + otherRect.getH(), _rect.y, _rect.y + _rect.h)) &&
		(abs(otherRect.getX() + otherRect.getW() - _rect.x) < otherRect.getCollisionTolerance() + _collisionTolerance)
		)
		return true;
	return false;
}

bool CustomRectangle::hasCollidedRight(const CustomRectangle& otherRect) const {
	if (
		(otherRect.getVelX() < 0) &&
		(CustomHelper::inBetween(otherRect.getY(), _rect.y, _rect.y + _rect.h) ||
			CustomHelper::inBetween(otherRect.getY() + otherRect.getH(), _rect.y, _rect.y + _rect.h)) &&
		(abs(otherRect.getX() - (_rect.x + _rect.w)) < otherRect.getCollisionTolerance() + _collisionTolerance)
		)
		return true;
	return false;
}

