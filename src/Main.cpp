#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <sstream>

using namespace sf;

const int NUM_BRANCHES = 6;

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
    TreeAlt,
    Bee,
    Cloud,
    Player,
    Branch,
    Log,
    Headstone,
    Axe,
    MaxTextures,
};

Texture loadRequiredTexture(std::string path) {
    try {
        Texture newTexture;
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

SoundBuffer loadRequiredSound(std::string path) {
    try {
        SoundBuffer newBuffer;
        if (const auto ok = newBuffer.loadFromFile(path); !ok) {
            std::cerr << "Failed to load sound: " << path << "\n";
            std::abort();
        }

        return newBuffer;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Failed to load sound: " << path << "\n";
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

enum class Side {
    Left,
    Right,
    None,
};

void updateBranches(std::array<Side, NUM_BRANCHES>& branchPositions) {
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    auto randInt = randomInt(0, 5);

    switch (randInt) {
        case 0:
            branchPositions[0] = Side::Left;
            break;

        case 1:
            branchPositions[0] = Side::Right;
            break;

        default:
            branchPositions[0] = Side::None;
            break;
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
    textures[(int)TextureId::Axe] = loadRequiredTexture("graphics/axe.png");
    textures[(int)TextureId::TreeAlt] =
        loadRequiredTexture("graphics/tree2.png");

    // Load fonts
    Font font = loadRequiredFont("fonts/KOMIKAP_.ttf");

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

    // Background Tree Setup
    auto treeSprite2 = Sprite{textures[(int)TextureId::TreeAlt]};
    auto treeSprite3 = Sprite{textures[(int)TextureId::TreeAlt]};
    auto treeSprite4 = Sprite{textures[(int)TextureId::TreeAlt]};
    auto treeSprite5 = Sprite{textures[(int)TextureId::TreeAlt]};
    auto treeSprite6 = Sprite{textures[(int)TextureId::TreeAlt]};

    treeSprite2.setPosition({300, -50});
    treeSprite3.setPosition({20, 0});
    treeSprite4.setPosition({1500, -40});
    treeSprite5.setPosition({1300, -25});
    treeSprite6.setPosition({1900, 0});

    // Player Setup
    auto playerSprite = Sprite{textures[(int)TextureId::Player]};
    playerSprite.setPosition({580, 720});
    auto playerSide = Side::Left;

    // Headstone Setup
    auto headstoneSprite = Sprite{textures[(int)TextureId::Headstone]};
    headstoneSprite.setPosition({600, 860});

    // Axe Setup
    auto axeSprite = Sprite{textures[(int)TextureId::Axe]};
    axeSprite.setPosition({700, 830});
    const int AXE_POSITION_LEFT = 700;
    const int AXE_POSITION_RIGHT = 1075;

    // Flying Log Setup
    auto logSprite = Sprite{textures[(int)TextureId::Log]};
    logSprite.setPosition({810, 720});
    auto logActive = bool{false};
    auto logSpeedX = float{1000};
    auto logSpeedY = float{-1500};

    // Input Detection
    auto acceptInput = bool{false};

    // Prepare Sound Buffers
    auto chopBuffer = loadRequiredSound("sounds/chop.wav");
    auto outOfTimeBuffer = loadRequiredSound("sounds/out_of_time.wav");
    auto deathBuffer = loadRequiredSound("sounds/death.wav");

    Sound chop = Sound{chopBuffer};
    chop.setVolume(60);
    Sound death = Sound{deathBuffer};
    death.setVolume(40);
    Sound outOfTime = Sound{outOfTimeBuffer};
    outOfTime.setVolume(40);

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

    Text messageText{font, "Press Enter to start!", 75};
    Text scoreText{font, "Score = 0", 100};

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.getCenter());
    messageText.setPosition({1920.0 / 2.0f, 1080.0 / 2.0f});

    scoreText.setPosition({20, 20});

    // Backgrounds for the text
    RectangleShape rect1;
    rect1.setFillColor(sf::Color(0, 0, 0, 150));
    auto bounds = scoreText.getLocalBounds();
    rect1.setSize({bounds.size.x + 50, 105});
    rect1.setPosition({0, 30});

    // Game State Variables
    bool paused{true};
    int score{0};
    std::array<Side, NUM_BRANCHES> branchPositions;
    std::array<Sprite, NUM_BRANCHES> branches = {
        Sprite{textures[(int)TextureId::Branch]},
        Sprite{textures[(int)TextureId::Branch]},
        Sprite{textures[(int)TextureId::Branch]},
        Sprite{textures[(int)TextureId::Branch]},
        Sprite{textures[(int)TextureId::Branch]},
        Sprite{textures[(int)TextureId::Branch]},
    };

    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setPosition({-2000, -2000});

        // The center of the branch so we can spin it without changing it's
        // position.
        branches[i].setOrigin({220, 20});
    }

    while (window.isOpen()) {
        // Handle events
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyReleased>()) {
                acceptInput = true;
                // hide the axe
                axeSprite.setPosition({2000, axeSprite.getPosition().y});
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
            paused = false;
            timeRemaining = 6.0f;
            score = 0;
            // Hide all branches to start
            for (int i = 0; i < NUM_BRANCHES; i++) {
                branchPositions[i] = Side::None;
            }
            headstoneSprite.setPosition({675, 2000});
            playerSprite.setPosition({580, 720});
            acceptInput = true;
        }

        // Update state
        auto dt = clock.restart();
        if (!paused) {
            if (acceptInput) {
                if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
                    playerSide = Side::Right;
                    score++;
                    timeRemaining += (int)(2 / score);
                    timeRemaining += 0.15;
                    axeSprite.setPosition(
                        {AXE_POSITION_RIGHT, axeSprite.getPosition().y});
                    playerSprite.setPosition({1200, 720});
                    updateBranches(branchPositions);
                    logSprite.setPosition({810, 720});
                    logSpeedX = -5000;
                    logActive = true;
                    acceptInput = false;
                    chop.play();
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
                    playerSide = Side::Left;
                    score++;
                    timeRemaining += (int)(2 / score) + 0.15;
                    axeSprite.setPosition(
                        {AXE_POSITION_LEFT, axeSprite.getPosition().y});
                    playerSprite.setPosition({580, 720});
                    updateBranches(branchPositions);
                    logSprite.setPosition({810, 720});
                    logSpeedX = 5000;
                    logActive = true;
                    acceptInput = false;
                    chop.play();
                }
            }

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
                outOfTime.play();
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

            // Update Score
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
            auto bounds = scoreText.getLocalBounds();
            rect1.setSize({bounds.size.x + 50, rect1.getSize().y});

            // Update branches
            for (int i = 0; i < NUM_BRANCHES; i++) {
                float height = i * 150;

                if (branchPositions[i] == Side::Left) {
                    branches[i].setPosition({610, height});
                    branches[i].setRotation(degrees(180));
                } else if (branchPositions[i] == Side::Right) {
                    branches[i].setPosition({1330, height});
                    branches[i].setRotation(degrees(0));
                } else {
                    // Hide the branch
                    branches[i].setPosition({3000, height});
                }
            }

            // Handle flying logs
            if (logActive) {
                logSprite.setPosition(
                    {logSprite.getPosition().x + (logSpeedX * dt.asSeconds()),
                     logSprite.getPosition().y + (logSpeedY * dt.asSeconds())});

                // Has the log reached the edge?
                if (logSprite.getPosition().x < -100 ||
                    logSprite.getPosition().x > 2000) {
                    logActive = false;
                    logSprite.setPosition({810, 720});
                }
            }

            // Cause of player death
            if (branchPositions[5] == playerSide) {
                paused = true;
                acceptInput = false;
                headstoneSprite.setPosition({525, 760});
                playerSprite.setPosition({2000, 660});
                messageText.setString("SQUISHED!!");
                auto textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.getCenter());
                messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});
                death.play();
            }
        }

        // Redraw scene
        window.clear();
        window.draw(backgroundImageSprite);
        window.draw(cloud1Sprite);
        window.draw(cloud2Sprite);
        window.draw(cloud3Sprite);

        // window.draw(treeSprite2);
        window.draw(treeSprite3);
        window.draw(treeSprite4);
        // window.draw(treeSprite5);
        window.draw(treeSprite6);

        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }

        window.draw(logSprite);
        window.draw(treeSprite);
        window.draw(playerSprite);
        window.draw(axeSprite);
        window.draw(headstoneSprite);
        window.draw(beeSprite);
        window.draw(rect1);
        window.draw(scoreText);

        window.draw(timeBar);

        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }
}