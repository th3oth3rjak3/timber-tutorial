#include "GameObject.hpp"

GameObject::GameObject(const sf::Texture& texture, sf::RenderWindow& window)
    : sprite(texture), window(window) {};

void GameObject::setPosition(float x, float y) {
    sprite.setPosition({x, y});
}

sf::Vector2f GameObject::getPosition() const {
    return sprite.getPosition();
}

void GameObject::render() const {
    window.draw(sprite);
}

bool GameObject::isActive() const {
    return active;
}

void GameObject::activate() {
    active = true;
}

void GameObject::deactivate() {
    active = false;
}