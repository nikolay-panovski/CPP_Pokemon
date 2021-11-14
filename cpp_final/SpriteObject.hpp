#pragma once

#include "GameObject.hpp"

class SpriteObject : public GameObject {
	private:
		std::string spriteFilename;
		sf::Texture texture;
		sf::Sprite sprite;

	public:
		SpriteObject();
		SpriteObject(Vec2f startPosition, std::string textureFilename);
		~SpriteObject();

		std::string GetSpriteFilename(void) const;
		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;

		void Render(sf::RenderWindow& window) override;
};