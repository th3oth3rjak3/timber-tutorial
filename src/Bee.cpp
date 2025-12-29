#include "Bee.hpp"

#include "Random.hpp"

Bee::Bee(const sf::Texture& texture, sf::RenderWindow& window)
    : GameObject(texture, window) {}

void Bee::activate() {
    speed = randomFloat(MIN_SPEED, MAX_SPEED);
    height = randomFloat(MIN_HEIGHT, MAX_HEIGHT);
    // Bee starts off the screen to the right at 2000 pixels and then moves
    // leftward.
    setPosition(2000, height);
    active = true;
}

void Bee::update(const sf::Time deltaTime) {
    const auto pixelsToTravel = speed * deltaTime.asSeconds();
    setPosition(getPosition().x - pixelsToTravel, getPosition().y);
}
