#pragma once

#include "SpriteArray.hpp"

SpriteArray::SpriteArray(std::initializer_list<std::string> il)
	: GameObject() {
	for (const std::string* it = begin(il); it != end(il); it++) {
		// can't avoid new, deal with this in memory!
		// TODO: fix positioning definition
		SpriteObject* sprFromFilename = new SpriteObject(/*this->GetPosition()*/ Vec2f(0.0f, 0.0f), *it);
		sprites.push_back(sprFromFilename);
	}
	activeSprite = sprites[0];
}

SpriteArray::~SpriteArray() {}

std::string SpriteArray::GetActiveSpriteFilename(void) const {
	return this->activeSprite->GetSpriteFilename();
}

void SpriteArray::SetActiveSprite(SpriteObject* sprite) {
	activeSprite = sprite;
}

Vec2f SpriteArray::GetPosition(void) const {
	return this->activeSprite->GetPosition();
}

void SpriteArray::SetPosition(Vec2f newPosition) {
	// probably needs to be different
	this->activeSprite->SetPosition(newPosition);
}

void SpriteArray::Render(sf::RenderWindow& window) {
	this->activeSprite->Render(window);
}