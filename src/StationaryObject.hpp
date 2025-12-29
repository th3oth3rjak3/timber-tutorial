#pragma once

#include "GameObject.hpp"

class StationaryObject : public GameObject {
public:
    explicit StationaryObject(const sf::Texture& texture,
                              sf::RenderWindow& window);

    // Hide the object offscreen, not used for stationary objects.
    void despawn() override {}

    // This is always false for a stationary object.
    bool shouldRespawn() const override {
        return false;
    }

    // Stationary objects don't move so this is unused.
    void update(const sf::Time deltaTime) override {};

    virtual ~StationaryObject() = default;
};