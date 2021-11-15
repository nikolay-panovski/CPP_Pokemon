#pragma once

#include "SpriteArray.hpp"

template<typename T>
SpriteArray::SpriteArray(T filename) 
	: GameObject() {
	sprites.push_back(&SpriteObject(this->GetPosition(), *filename));
}

template<typename T, typename... Args>
SpriteArray::SpriteArray(T nextFilename, Args... filenames) 
	: GameObject() {
	sprites.push_back(&SpriteObject(this->GetPosition(), *nextFilename));
	// bound to get executed every time - if in above template, will probably point to the last added object
	// (not that it would matter with *this* usage, but still)
	activeSprite = sprites[0];
	SpriteArray(filenames);
	printf("Address of SpriteArray: %p", &this);
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