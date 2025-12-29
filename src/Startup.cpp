#include "Startup.hpp"

#include "BackgroundImage.hpp"
#include "Bee.hpp"
#include "Cloud.hpp"
#include "Random.hpp"
#include "TextureManager.hpp"
#include "Tree.hpp"

void render(sf::RenderWindow& window,
            std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    window.clear();

    for (auto& obj : gameObjects) {
        obj->render();
    }

    window.display();
}

void updateState(std::vector<std::unique_ptr<GameObject>>& gameObjects,
                 sf::Time dt) {
    for (auto& obj : gameObjects) {
        if (obj->shouldRespawn()) {
            obj->spawn();
        } else {
            obj->update(dt);
        }
    }
}

void handleEvents(sf::RenderWindow& window) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        auto keyPress = event->getIf<sf::Event::KeyPressed>();
        if (keyPress != nullptr &&
            keyPress->code == sf::Keyboard::Key::Escape) {
            window.close();
        }
    }
}

void loadGameObjects(sf::RenderWindow& window, TextureManager& textures,
                     std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    // background image
    gameObjects.emplace_back(std::make_unique<BackgroundImage>(
        textures.get(TextureId::Background), window));
    gameObjects.back()->spawn();

    // clouds
    for (int i = 0; i < 3; i++) {
        gameObjects.emplace_back(
            std::make_unique<Cloud>(textures.get(TextureId::Cloud), window));
        auto x = randomFloat(-300, 1920);
        auto y = randomFloat(0, 150);
        gameObjects.back()->spawn({x, y});
    }

    // tree
    gameObjects.emplace_back(
        std::make_unique<Tree>(textures.get(TextureId::Tree), window));
    gameObjects.back()->spawn();

    // bee
    gameObjects.emplace_back(
        std::make_unique<Bee>(textures.get(TextureId::Bee), window));
    gameObjects.back()->spawn();
}