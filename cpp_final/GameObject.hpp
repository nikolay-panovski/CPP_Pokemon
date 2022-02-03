#pragma once

#include <string>
//#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;

class GameObject {
	//private:

	//protected:

	public:
		GameObject();
		~GameObject();

		virtual Vec2f GetPosition(void) const = 0;
		virtual void SetPosition(Vec2f newPosition) = 0;
		virtual void HandleEvent(const sf::Event& event, sf::RenderWindow& window);
		//virtual void Update(void) = 0;
		virtual void Render(sf::RenderWindow& window) = 0;
};