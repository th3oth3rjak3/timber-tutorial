#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>

// SFML 3 migration available here: https://github.com/donlaiq/sfml_migration/blob/main/timber/Timber.cpp

int main()
{
    constexpr sf::Vector2u windowSize(1920u, 1080u);
    const sf::VideoMode vm(windowSize);
    auto window = sf::RenderWindow(vm, "Timber!!!", sf::Style::Close);
    window.setFramerateLimit(144);
    sf::Texture textureBackground;
    if (const auto loaded = textureBackground.loadFromFile("graphics/background.png"); !loaded) {
        std::cout << "Failed to load background texture from file" << std::endl;
        return -1;
    }

    sf::Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition(sf::Vector2f{0, 0});

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            auto keyPress = event->getIf<sf::Event::KeyPressed>();
            if (keyPress != nullptr && keyPress->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }

        window.clear();

        window.draw(spriteBackground);
        window.display();
    }
}
