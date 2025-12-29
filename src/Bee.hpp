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

    // Setup the position and speed of the bee.
    void activate() override;

    // Update the position of the bee based on the elapsed time since the last
    // frame.
    void update(const sf::Time deltaTime);
};