#include "Button.hpp"

Button::Button(Vec2f startPosition, sf::Font& newFont, std::string buttonText, Vec2f size, sf::Color color) :
    GameObject(), font(newFont), textString(buttonText)
{
    this->isActive = true;
    this->hasTexture = false;

    this->shape.setSize(size);
    this->shape.setFillColor(color);
    /**this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(1);
    /**/

    this->text.setFont(font);
    this->text.setString(textString);
    this->text.setCharacterSize(26);
    this->text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width * 0.5f, textRect.top + textRect.height * 0.5f);

    this->SetPosition(startPosition);
}

Button::Button(Vec2f startPosition, sf::Font& newFont, std::string buttonText, std::string textureFilename) :
    GameObject(), font(newFont), textString(buttonText)
{
    this->isActive = true;

    this->hasTexture = this->texture.loadFromFile(textureFilename);
    this->sprite.setTexture(texture);

    this->shape.setSize(Vec2f(texture.getSize().x, texture.getSize().y));
    this->shape.setFillColor(sf::Color::Transparent);

    this->text.setFont(font);
    this->text.setString(textString);
    this->text.setCharacterSize(26);
    this->text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width * 0.5f, textRect.top + textRect.height * 0.5f);

    this->SetPosition(startPosition);
}

Button::~Button() { }

void Button::HandleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left) {

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f size = shape.getSize();
        sf::Vector2f position = shape.getPosition();

        if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
            mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {
            this->OnClick();
        }
    }
}

Vec2f Button::GetPosition(void) const {
    // sprite and shape positions *should* be functionally the same
    if (this->hasTexture == true) {
        return this->sprite.getPosition();
    }
    else return this->shape.getPosition();
}

void Button::SetPosition(const sf::Vector2f position) {
    this->shape.setPosition(position);
    sf::Vector2f size = this->shape.getSize();
    sf::Vector2f centerButton(position.x + (size.x / 2.0f), position.y + (size.y / 2.0f));
    this->text.setPosition(centerButton);
    if (this->hasTexture == true) {
        this->sprite.setPosition(position);
    }
}

void Button::ToggleActive(void) {
    this->isActive ^= true;
}

void Button::Render(sf::RenderWindow& window) {
    window.draw(this->shape);
    if (this->hasTexture == true) {
        window.draw(this->sprite);
    }
    window.draw(this->text);
}

void Button::OnClick(void) {
    if (this->isActive == true) {
        this->action();
    }
}

void Button::SetButtonAction(std::function<void()> action) {
    this->action = action;
}