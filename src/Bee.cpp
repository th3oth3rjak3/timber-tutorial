#include "Bee.hpp"

#include "Random.hpp"

// The amount of margin that the object should be off screen before respawning.
const int LEFT_SIDE_MARGIN = -20;

Bee::Bee(const sf::Texture& texture, sf::RenderWindow& window)
    : GameObject(texture, window) {}

void Bee::spawn() {
    height = randomFloat(MIN_HEIGHT, MAX_HEIGHT);
    // Bee starts off the screen to the right at 2000 pixels and then moves
    // leftward.
    spawn({2000, height});
}

void Bee::spawn(const sf::Vector2f& position) {
    speed = randomFloat(MIN_SPEED, MAX_SPEED);
    setPosition(position.x, position.y);
}

void Bee::update(const sf::Time deltaTime) {
    const auto pixelsToTravel = speed * deltaTime.asSeconds();
    setPosition(getPosition().x - pixelsToTravel, getPosition().y);
}

bool Bee::shouldRespawn() const {
    auto beeWidth = sprite.getTexture().getSize().x;
    auto rightSide = beeWidth + getPosition().x;
    return rightSide <= LEFT_SIDE_MARGIN;
}