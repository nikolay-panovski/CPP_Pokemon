#pragma once

#include <list>
#include "GameObject.hpp"

class Scene {
	private:
		const std::string id;
		std::list<GameObject*> objsInScene;

	public:
		Scene(std::string newID);
		~Scene();

		void AddGameObject(GameObject& object);
		void RemoveGameObject(GameObject& object);

		void HandleEvent(sf::Event& event, sf::RenderWindow& window);
		//void Update();
		void Render(sf::RenderWindow& window);
		std::string GetIdentifier() const;
};