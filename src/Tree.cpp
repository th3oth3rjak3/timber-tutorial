#include "Tree.hpp"

Tree::Tree(const sf::Texture& texture, sf::RenderWindow& window)
    : StationaryObject(texture, window) {}

void Tree::spawn() {
    spawn({810, 0});
}

void Tree::spawn(const sf::Vector2f& position) {
    speed = 0;
    sprite.setPosition(position);
}