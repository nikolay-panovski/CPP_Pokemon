#include "GameObject.hpp"

GameObject::GameObject() {}

GameObject::~GameObject() {
	//printf_s("GameObject destroyed successfully via unique_ptr.\n");
}

void GameObject::HandleEvent(const sf::Event& event, sf::RenderWindow& window) {

}