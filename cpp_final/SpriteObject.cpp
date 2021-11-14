#pragma once

#include "SpriteObject.hpp"

SpriteObject::SpriteObject(Vec2f startPosition, std::string textureFilename) :
	GameObject() {
	this->spriteFilename = textureFilename;
	this->texture.loadFromFile(spriteFilename);
	this->sprite.setTexture(texture);

	this->SetPosition(startPosition);
}

SpriteObject::~SpriteObject() {}

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