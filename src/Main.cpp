#include <SFML/Graphics.hpp>
#include <optional>

#include "BackgroundImage.hpp"
#include "Bee.hpp"
#include "Cloud.hpp"
#include "Random.hpp"
#include "TextureManager.hpp"
#include "Tree.hpp"

constexpr sf::Vector2u WINDOW_SIZE{1920u, 1080u};
const sf::VideoMode VIDEO_MODE{WINDOW_SIZE};

int main() {
    auto window = sf::RenderWindow{VIDEO_MODE, "Timber!!!", sf::Style::Close};
    window.setFramerateLimit(144);

    TextureManager textures;
    textures.loadAll();

    std::vector<std::unique_ptr<GameObject>> gameObjects;

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

    sf::Clock clock;
    while (window.isOpen()) {
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

        // Update state

        sf::Time dt = clock.restart();

        for (auto& obj : gameObjects) {
            if (obj->shouldRespawn()) {
                obj->spawn();
            } else {
                obj->update(dt);
            }
        }

        // Render

        window.clear();

        for (auto& obj : gameObjects) {
            obj->render();
        }

        window.display();
    }
}