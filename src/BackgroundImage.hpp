#pragma once

#include "StationaryObject.hpp"

class BackgroundImage : public StationaryObject {
public:
    explicit BackgroundImage(const sf::Texture& texture,
                             sf::RenderWindow& window);

    // Set the default position of the background image, speed is 0.
    void spawn() override;

    // Set a specific position for the background image with the default speed
    // of 0.
    void spawn(const sf::Vector2f& position) override;
};