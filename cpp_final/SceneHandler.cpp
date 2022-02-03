#include "SceneHandler.hpp"

SceneHandler::SceneHandler() { }

SceneHandler::~SceneHandler() { }

void SceneHandler::RenderCurrentScene(sf::RenderWindow& window) {
	if (this->scenes.size() > 0) {
		this->scenes.top()->Render(window);
	}
}

/**
void SceneHandler::UpdateCurrentScene(void) {
	if (this->scenes.size() > 0) {
		this->scenes.top()->Update();
	}
}
/**/

void SceneHandler::AddScene(Scene* sceneToAdd) {
	//printf_s(("Adding scene: " + sceneToAdd->GetIdentifier() + "\n").c_str());
	this->scenes.push(sceneToAdd);
}

void SceneHandler::PopCurrentScene(void) {
	this->scenes.pop();
}

Scene SceneHandler::currentScene(void) const {
	// never leave the scene stack empty!!
	return (*this->scenes.top());
}