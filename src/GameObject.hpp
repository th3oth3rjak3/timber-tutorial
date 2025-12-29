#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Sprite sprite;
    sf::RenderWindow& window;
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

    // Set the game object position and speed to defaults.
    virtual void spawn() = 0;

    // Set the game object position to the provided value.
    virtual void spawn(const sf::Vector2f& position) = 0;

    // Despawn the game object so it's not visible on the screen.
    virtual void despawn() = 0;

    // Determines when the game object should be respawned to its default
    // starting point.
    virtual bool shouldRespawn() const = 0;

    // Update the state for the game object.
    virtual void update(const sf::Time deltaTime) = 0;

    virtual ~GameObject() = default;
};