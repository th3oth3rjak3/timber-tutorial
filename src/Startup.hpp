#pragma once

#include "GameObject.hpp"
#include "TextureManager.hpp"

void render(sf::RenderWindow& window,
            std::vector<std::unique_ptr<GameObject>>& gameObjects);

void updateState(std::vector<std::unique_ptr<GameObject>>& gameObjects,
                 sf::Time dt);

void handleEvents(sf::RenderWindow& window);

void loadGameObjects(sf::RenderWindow& window, TextureManager& textures,
                     std::vector<std::unique_ptr<GameObject>>& gameObjects);