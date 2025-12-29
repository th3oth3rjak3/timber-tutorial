#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

class Bee : public GameObject {
private:
    static constexpr float MIN_SPEED = 200;
    static constexpr float MAX_SPEED = 399;
    static constexpr float MIN_HEIGHT = 500;
    static constexpr float MAX_HEIGHT = 999;

public:
    explicit Bee(const sf::Texture& texture, sf::RenderWindow& window);

    // Set the default speed and position of the bee.
    void spawn() override;

    // Set a specific position for the bee with the default speed.
    void spawn(const sf::Vector2f& position) override;

    // Hide the bee offscreen. Currently unused.
    void despawn() override {}

    // When the bee has flown offscreen this will be true.
    bool shouldRespawn() const override;

    // Update the position of the bee based on the elapsed time since the last
    // frame.
    void update(const sf::Time deltaTime) override;
};