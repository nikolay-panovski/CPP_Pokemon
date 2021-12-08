#pragma once

#include "SpriteArray.hpp"

SpriteArray::SpriteArray(std::initializer_list<std::string> il)
	: GameObject() {
	for (const std::string* it = begin(il); it != end(il); it++) {
		// TODO: fix positioning definition
		SpriteObject* sprFromFilename = new SpriteObject(/*this->GetPosition()*/ Vec2f(0.0f, 0.0f), *it);
		sprites.push_back(sprFromFilename);
	}
	activeSprite = sprites[0];

	// memory address readings to validate delete from this->destructor
	/**
	for (unsigned int i = 0; i < sprites.size(); i++) {
		printf_s("Address of sprites[%i]: %p\n", i, &sprites[i]);	// gives a difference of 4 between elements, it's a pointer array
		printf_s("Value of sprites[%i]: %p\n", i, sprites[i]);
	}
	/**/
}

SpriteArray::~SpriteArray() {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		delete sprites[i];
	}
	sprites.clear();
}

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