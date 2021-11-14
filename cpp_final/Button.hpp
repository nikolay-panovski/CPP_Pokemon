#pragma once

#include "GameObject.hpp"
#include <functional>

class Button : public GameObject {

    private:
        bool isActive;
        bool hasTexture;

        std::string textString;
        sf::Text text;
        sf::Font& font;
        sf::RectangleShape shape;
        sf::Texture texture;
        sf::Sprite sprite;

        std::function<void()> action;
    public:
        Button(Vec2f startPosition, sf::Font& newFont, std::string buttonText,
            Vec2f size, sf::Color color);
        Button(Vec2f startPosition, sf::Font& newFont, std::string buttonText,
            std::string textureFilename);
        ~Button();

        void HandleEvent(const sf::Event& event, sf::RenderWindow& window) override;

        Vec2f GetPosition(void) const override;
        void SetPosition(const sf::Vector2f position) override;
        void ToggleActive(void);

        void Render(sf::RenderWindow& window) override;

        virtual void OnClick(void);
        void SetButtonAction(std::function<void()> action);
        //void setCharacterSize(const int size);
};