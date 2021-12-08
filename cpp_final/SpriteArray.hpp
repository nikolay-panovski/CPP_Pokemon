#pragma once

#include "GameObject.hpp"
#include "SpriteObject.hpp"
#include <initializer_list>

class SpriteArray : public GameObject {
	private:
		std::vector<SpriteObject*> sprites;
		SpriteObject** activeSprite;

	public:
		SpriteArray(Vec2f newPosition, std::initializer_list<std::string> il);
		~SpriteArray();

		std::string GetActiveSpriteFilename(void) const;
		void SetActiveSprite(SpriteObject** sprite);
		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;

		void IncrementActiveSprite(void);
		void DecrementActiveSprite(void);

		void Render(sf::RenderWindow& window) override;
};