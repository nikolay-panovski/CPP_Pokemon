#pragma once

#include "GameObject.hpp"
#include "SpriteObject.hpp"

class SpriteArray : public GameObject {
	private:
		std::vector<SpriteObject*> sprites;
		SpriteObject* activeSprite;

	public:
		SpriteArray(std::string* filenames[]);
		~SpriteArray();

		std::string GetSpriteFilename(void) const;
		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;

		void Render(sf::RenderWindow& window) override;
};