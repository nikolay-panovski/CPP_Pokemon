#pragma once

#include "SpriteArray.hpp"

SpriteArray::SpriteArray(Vec2f newPosition, std::initializer_list<std::string> il)
	: GameObject() {
	for (const std::string* it = begin(il); it != end(il); it++) {
		// TODO: fix positioning definition
		SpriteObject* sprFromFilename = new SpriteObject(/*this->GetPosition()*/ Vec2f(0.0f, 0.0f), *it);
		sprites.push_back(sprFromFilename);
	}
	activeSprite = &sprites[0];
	this->SetPosition(newPosition);

	// memory address readings to validate delete from this->destructor
	/**
	for (unsigned int i = 0; i < sprites.size(); i++) {
		printf_s("Address of sprites[%i]: %p\n", i, &sprites[i]);	// gives a difference of 4 between elements, it's a pointer array
		printf_s("Value of activeSprite: %p\n", activeSprite);
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
	return (**activeSprite).GetSpriteFilename();
}

void SpriteArray::SetActiveSprite(SpriteObject** sprite) {
	activeSprite = sprite;
}

Vec2f SpriteArray::GetPosition(void) const {
	return (**activeSprite).GetPosition();
}

void SpriteArray::SetPosition(Vec2f newPosition) {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		sprites[i]->SetPosition(newPosition);
	}
}

void SpriteArray::IncrementActiveSprite(void) {
	if (activeSprite == &sprites[sprites.size() - 1]) {
		this->SetActiveSprite(&sprites[0]);
	}
	else this->activeSprite++;
}

void SpriteArray::DecrementActiveSprite(void) {
	if (activeSprite == &sprites[0]) {
		this->SetActiveSprite(&sprites[sprites.size() - 1]);
	}
	else this->activeSprite--;
}

void SpriteArray::Render(sf::RenderWindow& window) {
	(**activeSprite).Render(window);
}