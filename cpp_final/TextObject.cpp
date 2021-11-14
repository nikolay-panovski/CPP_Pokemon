

#include "TextObject.hpp"

TextObject::TextObject(Vec2f startPosition, sf::Font& startFont, std::string startText) :
	GameObject(), font(startFont), text(startText, font) {
	this->SetPosition(startPosition);
	this->SetText(startText);
	this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::White);
}

TextObject::~TextObject() {
	//printf("destroyed a text");
}

std::string TextObject::GetText(void) const {
	return this->textString;
}

void TextObject::SetText(std::string newText) {
	this->textString = newText;
	this->text.setString(textString);
}

Vec2f TextObject::GetPosition(void) const {
	return this->text.getPosition();
}

void TextObject::SetPosition(Vec2f newPosition) {
	this->text.setPosition(newPosition);
}


void TextObject::Render(sf::RenderWindow& window) {
	window.draw(this->text);
}