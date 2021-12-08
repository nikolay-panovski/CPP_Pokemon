#pragma once

#include "SpriteObject.hpp"

SpriteObject::SpriteObject(Vec2f startPosition, std::string textureFilename) :
	GameObject() {
	this->spriteFilename = textureFilename;
	this->texture.loadFromFile(spriteFilename);
	this->sprite.setTexture(texture);

	this->SetPosition(startPosition);
}

SpriteObject::~SpriteObject() {
	/**
	printf_s("SpriteObject at address %p destroyed.\n", this);
	// line below returns 344. smallest (but not only) difference between array SpriteObjects is 188, though.
	printf_s("Size of this SpriteObject: %i\n", sizeof(SpriteObject));
	/**/
}

std::string SpriteObject::GetSpriteFilename(void) const {
	return this->spriteFilename;
}

Vec2f SpriteObject::GetPosition(void) const {
	return this->sprite.getPosition();
}

void SpriteObject::SetPosition(Vec2f newPosition) {
	this->sprite.setPosition(newPosition);
}

void SpriteObject::Render(sf::RenderWindow& window) {
	window.draw(this->sprite);
}