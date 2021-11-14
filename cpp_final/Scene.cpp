#include "Scene.hpp"

Scene::Scene(std::string newID) : id(newID) { }

Scene::~Scene() { }

void Scene::AddGameObject(GameObject& object) {
    this->objsInScene.push_back(&object);
}

void Scene::RemoveGameObject(GameObject& object) {
    this->objsInScene.erase(std::remove(objsInScene.begin(), objsInScene.end(), &object));
}

void Scene::HandleEvent(sf::Event& event, sf::RenderWindow& window) {
    for (std::list<GameObject*>::iterator it = objsInScene.begin(); it != objsInScene.end(); it++) {
        (*it)->HandleEvent(event, window);
    }
}

/**
void Scene::Update() {
    for (std::list<GameObject*>::iterator it = objsInScene.begin(); it != objsInScene.end(); it++) {
        (*it)->Update();
    }
}
/**/

void Scene::Render(sf::RenderWindow& window) {
    for (std::list<GameObject*>::iterator it = objsInScene.begin(); it != objsInScene.end(); it++) {
        (*it)->Render(window);
    }
}

std::string Scene::GetIdentifier() const {
    return this->id;
}