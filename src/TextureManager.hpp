#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class TextureId {
    Background,
    Tree,
    Bee,
    Cloud,
    Player,
    Branch,
    Log,
    Headstone,
};

class TextureManager {
    std::unordered_map<TextureId, sf::Texture> textures;

public:
    void load(TextureId id, const std::string& filepath);
    sf::Texture& get(TextureId id);
    void loadAll();
};
