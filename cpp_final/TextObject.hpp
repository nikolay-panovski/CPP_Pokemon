#pragma once

#include "GameObject.hpp"
//#include <SFML/Graphics.hpp>
//#include <string>

class TextObject : public GameObject {
	private:
		sf::Font font;
		sf::Text text;
		std::string textString;

	public:
		TextObject(Vec2f startPosition, sf::Font& startFont, std::string startText = "");
		~TextObject();

		std::string GetText(void) const;
		void SetText(std::string newText);

		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;

		void Render(sf::RenderWindow& window) override;
};