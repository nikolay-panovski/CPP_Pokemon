#pragma once

#include "SpriteArray.hpp"

SpriteArray::SpriteArray(std::string* filenames[]) 
	: GameObject() {
	for (std::string* s : filenames) {

	}
}

SpriteArray::~SpriteArray() {}

std::string SpriteArray::GetSpriteFilename(void) const {
	return this->spriteFilename;
}

Vec2f SpriteArray::GetPosition(void) const {
	return this->sprite.getPosition();
}

void SpriteArray::SetPosition(Vec2f newPosition) {
	this->sprite.setPosition(newPosition);
}

void SpriteArray::Render(sf::RenderWindow& window) {
	window.draw(this->sprite);
}