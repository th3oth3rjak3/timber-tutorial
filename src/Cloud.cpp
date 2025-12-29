#include "Cloud.hpp"

#include <SFML/Graphics/Texture.hpp>

#include "Random.hpp"

Cloud::Cloud(const sf::Texture& texture, sf::RenderWindow& window)
    : GameObject(texture, window) {}

void Cloud::spawn() {
    height = randomFloat(MIN_HEIGHT, MAX_HEIGHT);
    spawn({-300, height});
}

void Cloud::spawn(const sf::Vector2f& position) {
    speed = randomFloat(MIN_SPEED, MAX_SPEED);
    setPosition(position.x, position.y);
}

void Cloud::update(const sf::Time deltaTime) {
    sprite.move({speed * deltaTime.asSeconds(), 0.0f});
}

bool Cloud::shouldRespawn() const {
    auto windowWidth = window.getSize().x;
    return getPosition().x >= (windowWidth + 50);
}