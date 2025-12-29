#include "Cloud.hpp"

#include <SFML/Graphics/Texture.hpp>

#include "Random.hpp"

Cloud::Cloud(const sf::Texture& texture, sf::RenderWindow& window)
    : GameObject(texture, window) {}

void Cloud::activate() {
    speed = randomFloat(MIN_SPEED, MAX_SPEED);
    height = randomFloat(MIN_HEIGHT, MAX_HEIGHT);
    setPosition(-300, height);
    active = true;
}

void Cloud::activate(const sf::Vector2f& position) {
    speed = randomFloat(MIN_SPEED, MAX_SPEED);
    setPosition(position.x, position.y);
    active = true;
}

void Cloud::update(const sf::Time deltaTime) {
    sprite.move({speed * deltaTime.asSeconds(), 0.0f});
}