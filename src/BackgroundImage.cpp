#include "BackgroundImage.hpp"

BackgroundImage::BackgroundImage(const sf::Texture& texture,
                                 sf::RenderWindow& window)
    : StationaryObject(texture, window) {}

void BackgroundImage::spawn() {
    spawn({0, 0});
}

void BackgroundImage::spawn(const sf::Vector2f& position) {
    speed = 0;
    sprite.setPosition(position);
}