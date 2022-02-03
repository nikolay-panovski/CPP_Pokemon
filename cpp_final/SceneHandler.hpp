#pragma once

#include "Scene.hpp"
#include <stack>

class SceneHandler {
    private:
        std::stack<Scene*> scenes;

    public:
        SceneHandler();
        ~SceneHandler();

        void RenderCurrentScene(sf::RenderWindow& window);
        //void UpdateCurrentScene();

        void AddScene(Scene* sceneToAdd);
        void PopCurrentScene(void);
        Scene currentScene(void) const;
};