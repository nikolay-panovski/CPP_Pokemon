#pragma once

#include "GameObject.hpp"
#include "SpriteObject.hpp"

class SpriteArray : public GameObject {
	private:
		std::vector<SpriteObject*> sprites;
		SpriteObject* activeSprite;

	public:
		template<typename T>
		SpriteArray(T nextFilename);
		template<typename T, typename... Args>
		SpriteArray(T nextFilename, Args... filenames);
		~SpriteArray();

		std::string GetActiveSpriteFilename(void) const;
		void SetActiveSprite(SpriteObject* sprite);
		Vec2f GetPosition(void) const override;
		void SetPosition(Vec2f newPosition) override;

		void Render(sf::RenderWindow& window) override;
};