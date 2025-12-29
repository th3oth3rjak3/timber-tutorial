#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Sprite sprite;
    sf::RenderWindow& window;
    bool active = false;
    float speed = 0.0f;
    float height = 0.0f;

public:
    explicit GameObject(const sf::Texture& texture, sf::RenderWindow& window);

    // Set the position of the sprite.
    void setPosition(float x, float y);

    // Get the current position of the sprite.
    sf::Vector2f getPosition() const;

    // Render the sprite on the screen.
    void render() const;

    // If the sprite is actively moving, this will be true, otherwise false.
    bool isActive() const;

    // Activate the game object to perform some action.
    virtual void activate();

    // Deactivate the game object to stop some action.
    virtual void deactivate();

    virtual ~GameObject() = default;
};