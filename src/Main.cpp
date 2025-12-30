#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <sstream>

using namespace sf;

inline std::mt19937 rng(std::random_device{}());

inline int randomInt(const int min, const int max) {
    std::uniform_int_distribution dist(min, max);
    return dist(rng);
}

inline float randomFloat(const float min, const float max) {
    std::uniform_real_distribution dist(min, max);
    return dist(rng);
}

constexpr Vector2u WINDOW_SIZE{1920u, 1080u};
const VideoMode VIDEO_MODE{WINDOW_SIZE};

enum class TextureId : int {
    Background,
    Tree,
    Bee,
    Cloud,
    Player,
    Branch,
    Log,
    Headstone,
    MaxTextures,
};

sf::Texture loadRequiredTexture(std::string path) {
    try {
        sf::Texture newTexture;
        if (const auto ok = newTexture.loadFromFile(path); !ok) {
            std::cerr << "Failed to load texture: " << path << "\n";
            std::abort();
        }

        return newTexture;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << path << "\n";
        std::abort();
    }
}

Font loadRequiredFont(std::string path) {
    try {
        Font font;
        if (const auto ok = font.openFromFile(path); !ok) {
            std::cerr << "Failed to load font: " << path << "\n";
            std::abort();
        }

        return font;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load font: " << path << "\n";
        std::abort();
    }
}

int main() {
    auto window = RenderWindow{VIDEO_MODE, "Timber!!!", Style::Close};
    window.setFramerateLimit(144);

    // Load All Textures
    std::array<Texture, static_cast<int>(TextureId::MaxTextures)> textures;
    textures[(int)TextureId::Background] =
        loadRequiredTexture("graphics/background.png");
    textures[(int)TextureId::Bee] = loadRequiredTexture("graphics/bee.png");
    textures[(int)TextureId::Branch] =
        loadRequiredTexture("graphics/branch.png");
    textures[(int)TextureId::Cloud] = loadRequiredTexture("graphics/cloud.png");
    textures[(int)TextureId::Tree] = loadRequiredTexture("graphics/tree.png");
    textures[(int)TextureId::Player] =
        loadRequiredTexture("graphics/player.png");
    textures[(int)TextureId::Log] = loadRequiredTexture("graphics/log.png");
    textures[(int)TextureId::Headstone] =
        loadRequiredTexture("graphics/rip.png");

    // Background image
    auto backgroundImageSprite = Sprite{textures[(int)TextureId::Background]};
    backgroundImageSprite.setPosition({0, 0});

    // Bee Setup
    auto beeSprite = Sprite{textures[(int)TextureId::Bee]};
    auto beeActive = false;
    auto beeSpeed = 0.0f;
    beeSprite.setPosition({2000, 0});

    // Cloud 1 Setup
    auto cloud1Sprite = Sprite{textures[(int)TextureId::Cloud]};
    auto cloud1Active = true;
    auto cloud1Speed = randomFloat(25, 100);
    auto cloud1StartingX = randomFloat(0, 1920);
    auto cloud1StartingY = randomFloat(0, 150);
    cloud1Sprite.setPosition({cloud1StartingX, cloud1StartingY});

    // Cloud 2 setup
    auto cloud2Sprite = Sprite{textures[(int)TextureId::Cloud]};
    auto cloud2Active = true;
    auto cloud2Speed = randomFloat(25, 100);
    auto cloud2StartingX = randomFloat(0, 1920);
    auto cloud2StartingY = randomFloat(0, 150);
    cloud2Sprite.setPosition({cloud2StartingX, cloud2StartingY});

    // Cloud 3 setup
    auto cloud3Sprite = Sprite{textures[(int)TextureId::Cloud]};
    auto cloud3Active = true;
    auto cloud3Speed = randomFloat(25, 100);
    auto cloud3StartingX = randomFloat(0, 1920);
    auto cloud3StartingY = randomFloat(0, 150);
    cloud3Sprite.setPosition({cloud3StartingX, cloud3StartingY});

    // Tree Setup
    auto treeSprite = Sprite{textures[(int)TextureId::Tree]};
    treeSprite.setPosition({810, 0});

    Clock clock;

    // Time bar for player countdown
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize({timeBarStartWidth, timeBarHeight});
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(
        {(1920.0f / 2.0f) - (timeBarStartWidth / 2.0f), 980.0f});

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused{true};
    int score{0};

    Font font = loadRequiredFont("fonts/KOMIKAP_.ttf");

    Text messageText{font, "Press Enter to start!", 75};
    Text scoreText{font, "Score = 0", 100};

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.getCenter());
    messageText.setPosition({1920.0 / 2.0f, 1080.0 / 2.0f});

    scoreText.setPosition({20, 20});

    while (window.isOpen()) {
        // Handle events
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            auto keypress = event->getIf<Event::KeyPressed>();
            if (keypress != nullptr) {
                switch (keypress->code) {
                    case Keyboard::Key::Escape:
                        window.close();
                        break;
                    case Keyboard::Key::Enter:
                        paused = false;
                        timeRemaining = 6.0f;
                        score = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        // Update state
        auto dt = clock.restart();
        if (!paused) {
            // Update remaining time
            timeRemaining -= dt.asSeconds();

            // shrink time bar
            timeBar.setSize(
                {timeBarWidthPerSecond * timeRemaining, timeBarHeight});

            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of time!!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.getCenter());
                messageText.setPosition({1920.0f / 2.0f, 1080.0f / 2.0f});
            }

            // Cloud state updates
            if (!cloud1Active) {
                cloud1Speed = randomFloat(25, 100);
                cloud1Sprite.setPosition({-300, randomFloat(0, 150)});
                cloud1Active = true;
            } else {
                auto distance = cloud1Speed * dt.asSeconds();
                cloud1Sprite.move({distance, 0});

                if (cloud1Sprite.getPosition().x > 1920) {
                    cloud1Active = false;
                }
            }

            if (!cloud2Active) {
                cloud2Speed = randomFloat(25, 100);
                cloud2Sprite.setPosition({-300, randomFloat(0, 150)});
                cloud2Active = true;
            } else {
                auto distance = cloud2Speed * dt.asSeconds();
                cloud2Sprite.move({distance, 0});

                if (cloud2Sprite.getPosition().x > 1920) {
                    cloud2Active = false;
                }
            }

            if (!cloud3Active) {
                cloud3Speed = randomFloat(25, 100);
                cloud3Sprite.setPosition({-300, randomFloat(0, 150)});
                cloud3Active = true;
            } else {
                auto distance = cloud3Speed * dt.asSeconds();
                cloud3Sprite.move({distance, 0});

                if (cloud3Sprite.getPosition().x > 1920) {
                    cloud3Active = false;
                }
            }

            // Bee state updates
            if (!beeActive) {
                beeSpeed = randomFloat(200, 399);
                beeSprite.setPosition({2000, randomFloat(500, 999)});
                beeActive = true;
            } else {
                auto distance = beeSpeed * dt.asSeconds();
                beeSprite.move({distance * -1, 0});

                if (beeSprite.getPosition().x < -200) {
                    beeActive = false;
                }
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        // Redraw scene
        window.clear();
        window.draw(backgroundImageSprite);
        window.draw(cloud1Sprite);
        window.draw(cloud2Sprite);
        window.draw(cloud3Sprite);
        window.draw(treeSprite);
        window.draw(beeSprite);
        window.draw(scoreText);

        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }
}