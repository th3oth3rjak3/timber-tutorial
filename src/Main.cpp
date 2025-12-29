#include <SFML/Graphics.hpp>

#include "Startup.hpp"
#include "TextureManager.hpp"

constexpr sf::Vector2u WINDOW_SIZE{1920u, 1080u};
const sf::VideoMode VIDEO_MODE{WINDOW_SIZE};

int main() {
    auto window = sf::RenderWindow{VIDEO_MODE, "Timber!!!", sf::Style::Close};
    window.setFramerateLimit(144);

    TextureManager textures;
    textures.loadAll();

    std::vector<std::unique_ptr<GameObject>> gameObjects;
    loadGameObjects(window, textures, gameObjects);

    sf::Clock clock;
    while (window.isOpen()) {
        handleEvents(window);
        sf::Time dt = clock.restart();
        updateState(gameObjects, dt);
        render(window, gameObjects);
    }
}