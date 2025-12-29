#pragma once

#include "StationaryObject.hpp"

class Tree : public StationaryObject {
public:
    explicit Tree(const sf::Texture& texture, sf::RenderWindow& window);

    // Set the default position of the tree, speed is 0.
    void spawn() override;

    // Set a specific position for the tree with the default speed of 0.
    void spawn(const sf::Vector2f& position) override;
};