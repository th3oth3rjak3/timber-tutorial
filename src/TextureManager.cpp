#include "TextureManager.hpp"

#include <iostream>

void TextureManager::load(const TextureId id, const std::string& filepath) {
    try {
        if (const auto ok = textures[id].loadFromFile(filepath); !ok) {
            std::cout << "Failed to load texture: " << filepath << std::endl;
            std::abort();
        }
    } catch (const std::exception& e) {
        std::cout << "Failed to load texture: " << filepath << std::endl;
        std::abort();
    }
}

sf::Texture& TextureManager::get(const TextureId id) {
    return textures.at(id);
}

void TextureManager::loadAll() {
    load(TextureId::Background, "graphics/background.png");
    load(TextureId::Tree, "graphics/tree.png");
    load(TextureId::Bee, "graphics/bee.png");
    load(TextureId::Cloud, "graphics/cloud.png");
    load(TextureId::Player, "graphics/player.png");
    load(TextureId::Branch, "graphics/branch.png");
    load(TextureId::Log, "graphics/log.png");
    load(TextureId::Headstone, "graphics/rip.png");
}