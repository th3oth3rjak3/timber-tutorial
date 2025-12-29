#include <SFML/Graphics.hpp>
#include <optional>

#include "Bee.hpp"
#include "Cloud.hpp"
#include "Random.hpp"
#include "TextureManager.hpp"

constexpr sf::Vector2u WINDOW_SIZE{1920u, 1080u};
const sf::VideoMode VIDEO_MODE{WINDOW_SIZE};

int main() {
    auto window = sf::RenderWindow{VIDEO_MODE, "Timber!!!", sf::Style::Close};
    window.setFramerateLimit(144);

    TextureManager textures;
    textures.loadAll();

    auto backgroundSprite = sf::Sprite{textures.get(TextureId::Background)};
    backgroundSprite.setPosition({0, 0});

    auto treeSprite = sf::Sprite{textures.get(TextureId::Tree)};
    treeSprite.setPosition({810, 0});

    auto bee = Bee(textures.get(TextureId::Bee), window);
    bee.setPosition(0, 800);

    std::vector<Cloud> clouds;
    clouds.reserve(3);

    clouds.emplace_back(textures.get(TextureId::Cloud), window);
    clouds.emplace_back(textures.get(TextureId::Cloud), window);
    clouds.emplace_back(textures.get(TextureId::Cloud), window);

    for (auto& cloud : clouds) {
        auto x = randomFloat(-300, 1920);
        auto y = randomFloat(0, 150);
        cloud.activate({x, y});
    }

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

        /*
         * Update the scene
         */

        sf::Time dt = clock.restart();

        if (!bee.isActive()) {
            bee.activate();
        } else {
            bee.update(dt);
            // Bee is offscreen to the left.
            if (bee.getPosition().x < -100) {
                bee.deactivate();
            }
        }

        for (auto& cloud : clouds) {
            if (!cloud.isActive()) {
                cloud.activate();
            } else {
                cloud.update(dt);
                if (cloud.getPosition().x > 1920) {
                    cloud.deactivate();
                }
            }
        }

        /*
         * Display the scene
         */

        window.clear();

        // objects must be drawn back to front
        window.draw(backgroundSprite);

        // clouds go behind the tree.
        for (auto& cloud : clouds) {
            cloud.render();
        }

        window.draw(treeSprite);

        // bee goes in front of the tree to distract the player.
        bee.render();
        window.display();
    }
}