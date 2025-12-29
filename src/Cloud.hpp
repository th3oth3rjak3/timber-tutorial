#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

class Cloud : public GameObject {
private:
    static constexpr float MIN_SPEED = 25;
    static constexpr float MAX_SPEED = 100;
    static constexpr float MIN_HEIGHT = 1;
    static constexpr float MAX_HEIGHT = 150;

public:
    explicit Cloud(const sf::Texture& texture, sf::RenderWindow& window);

    // Set the start position for the cloud and the appropriate speed.
    void spawn() override;

    // Spawn the cloud at a specific position (first-frame or custom
    // placement)
    void spawn(const sf::Vector2f& position) override;

    // True when the cloud has gone off the right side of the screen.
    bool shouldRespawn() const override;

    // Hide the cloud, currently unused.
    void despawn() override {};

    // Update the position of the cloud based on the elapsed delta time.
    void update(const sf::Time deltaTime) override;
};