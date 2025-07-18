#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <random>
#include <chrono>


#include "TileMap.hpp"
#include "MapGenerator.hpp"
#include "Collision.hpp"
#include "CombatManager.hpp"
#include "EnemyFactory.hpp"

std::string playerSpritePath = "Sprites/Entities/Rogue.png";
std::string enemySpritePath = "Sprites/Entities/Pink_Slime.png";
std::string skeletonSpritePath = "Sprites/Entities/Skeleton_Mob.png";


void LoadFont(sf::Font& font, std::string str) {

    if (!font.openFromFile(str)) {
        std::cerr << "ERROR::COULD NOT LOAD FILE" << str << "!!!" << std::endl;
    }
}

enum directions {up, down, left, right};
enum class GameState {
    Exploration,
    Combat
};

void PollEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
        }
    }
}

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int width = 640;
	unsigned int height = 360;
    srand(time(NULL));

    sf::RenderWindow *window = new sf::RenderWindow(desktop, "Death's Edge", sf::Style::Resize);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);

    sf::Clock clock;
    //Tile Map

    TileMap tilemap;

    sf::Vector2u tileSize(32, 32);
    GeneratedMap mapData = MapGenerator::generateBSPMap(50, 30);
    std::vector<std::vector<int>>& level = mapData.tiles;
    std::vector<Room>& rooms = mapData.rooms;

    if (!tilemap.load("Sprites/Maps/Stone_Tiles.png", tileSize, level)) {
        std::cerr << "Failed to load tilemap." << std::endl;
        return -1;
    }

    // Set up Player Sprite
    sf::Texture playerTexture;

    if (!playerTexture.loadFromFile(playerSpritePath)) {
        std::cerr << "ERROR::COULD NOT LOAD FILE:: " << playerSpritePath << std::endl;
        return -1;
    }

    sf::Sprite playerSprite(playerTexture);
    int animationFrame = 0;
	float animationTimer = 0.f;
	float animationSpeed = 0.15f;
    sf::IntRect dir[4][4];
    for (int d = 0; d < 4; d++) {
        for (int f = 0; f < 4; f++) {
            dir[d][f] = sf::IntRect(sf::Vector2i(32 * f, 32 * d), sf::Vector2i(32, 32));
        }
    }


    playerSprite.setTextureRect(dir[down][0]);

    sf::CircleShape shadow(5.f);
    shadow.setScale(sf::Vector2f(2, 2));
    shadow.setOrigin(shadow.getGeometricCenter());
    shadow.setFillColor(sf::Color(0, 0, 0, 200));

    // Set up enemy Sprite
    sf::Texture enemyTexture;

    if (!enemyTexture.loadFromFile(enemySpritePath)) {
        std::cerr << "ERROR:: COULD NOT LOAD FILE:: " << enemySpritePath << std::endl;
        return -1;
    }

    sf::Sprite enemySprite(enemyTexture);

    sf::Texture skeletonTexture;

    if (!skeletonTexture.loadFromFile(skeletonSpritePath)) {
        std::cerr << "ERROR:: COULD NOT LOAD FILE:: " << skeletonSpritePath << std::endl;
        return -1;
    }
    
    sf::Sprite skeletonSprite(skeletonTexture);
	skeletonSprite.setTextureRect(dir[down][0]);
    // Set up View
    sf::View gameView(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(800, 600)));
    sf::View uiView;

    sf::Vector2f playerSpawn;
    sf::Vector2f enemySpawn;
    sf::Vector2f skeletonSpawn;
    if (!rooms.empty()) {
        // Spawn Player in first room
        Room& firstRoom = rooms[0];
        playerSpawn.x = (firstRoom.x + firstRoom.width / 2) * tileSize.x;
        playerSpawn.y = (firstRoom.y + firstRoom.height / 2) * tileSize.y;
        playerSprite.setPosition(playerSpawn);

        // Spawn Enemy in second room
        Room& secondRoom = rooms[1];
        enemySpawn.x = (secondRoom.x + secondRoom.width / 2) * tileSize.x;
        enemySpawn.y = (secondRoom.y + secondRoom.height / 2) * tileSize.y;
        enemySprite.setPosition(enemySpawn);

        Room& thirdRoom = rooms[2];
        skeletonSpawn.x = (thirdRoom.x + thirdRoom.width / 2) * tileSize.x;
        skeletonSpawn.y = (thirdRoom.y + thirdRoom.height / 2) * tileSize.y;
        skeletonSprite.setPosition(skeletonSpawn);
    }

    gameView.setCenter(playerSprite.getPosition());
    window->setView(gameView);

    GameState currentState = GameState::Exploration;

    CombatManager* combat = nullptr;
    Player* combatPlayer =new Player("Rogue", 100, 100, 10, 3);
    combatPlayer->setSpritePath(playerSpritePath);
    combatPlayer->addItem(new HealthPotion("Small Health Potion", 20));
    combatPlayer->addItem(new HealthPotion("Small Health Potion", 20));
    combatPlayer->addItem(new HealthPotion("Small Health Potion", 20));
    Enemy* currentEnemy = nullptr;
    Enemy* combatEnemy = EnemyFactory::create("Slime");
    Enemy* combatEnemy1 = EnemyFactory::create("Skeleton");

	while (window->isOpen()) {
        PollEvents(*window);
        float speed = 100.f; // pixels per second
        float dt = clock.restart().asSeconds();

        // Render
        window->clear();

        if (currentState == GameState::Exploration) {
            int direction = -1;
            bool isMoving = false;
            sf::Vector2f movement(0.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
                movement.y -= speed * dt;
				direction = up;
				isMoving = true;    
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
                movement.y += speed * dt;
				direction = down;  
				isMoving = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
                movement.x -= speed * dt;
				direction = left;
				isMoving = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
                movement.x += speed * dt;
				direction = right;
				isMoving = true;
            }

            if (isMoving) {
                // Update animation frame
                animationTimer += dt;
                if (animationTimer >= animationSpeed) {
                    animationTimer = 0.f;
                    animationFrame = (animationFrame + 1) % 4; // Cycle through frames
                }
                playerSprite.setTextureRect(dir[direction][animationFrame]);
            } else {
                animationFrame = 0; // Reset to first frame when not moving
                if (direction != -1) {
                    playerSprite.setTextureRect(dir[direction][0]); // Set to first frame of the current direction
				}
			}

            sf::FloatRect nextBounds = playerSprite.getGlobalBounds();
            nextBounds.position.x += movement.x;
            nextBounds.position.y += movement.y;

            if (!Collision::isMapColliding(level, nextBounds, (tileSize.x))) {
                playerSprite.move(movement);
            }

            gameView.setCenter(playerSprite.getPosition());
            window->setView(gameView);

            if (Collision::isSpriteColliding(playerSprite, enemySprite)) {
                currentEnemy = combatEnemy;
                combat = new CombatManager(combatPlayer, currentEnemy);
                currentState = GameState::Combat;
                continue;
            }
            if (Collision::isSpriteColliding(playerSprite, skeletonSprite)) {
                currentEnemy = combatEnemy1;
                combat = new CombatManager(combatPlayer, currentEnemy);
                currentState = GameState::Combat;
                continue;
            }

            shadow.setPosition(sf::Vector2f(playerSprite.getPosition().x + 16, playerSprite.getPosition().y + 32));

            // Draw to screen 
            window->draw(tilemap);
            window->draw(shadow);
            window->draw(playerSprite);
            window->draw(enemySprite);
            window->draw(skeletonSprite);

        } else if (currentState == GameState::Combat) {
            uiView = window->getDefaultView();
            window->setView(uiView);
            CombatOutcome result = combat->combatStatus(*window);
            if (result != CombatOutcome::Ongoing) {
                currentState = GameState::Exploration;
                
                if ((result == CombatOutcome::PlayerVictory || result == CombatOutcome::RunSuccess) && currentEnemy) {
                    // Move Sprite off screen for now
                    if (currentEnemy == combatEnemy) {
                        enemySprite.setPosition(sf::Vector2f(-1000, -1000));
                    }
                    else if (currentEnemy == combatEnemy1) {
                        skeletonSprite.setPosition(sf::Vector2f(-1000, -1000));
                    }
                    
                    delete currentEnemy;
                    currentEnemy = nullptr;
                }
                
                delete combat;
                combat = nullptr;

                window->setView(gameView);
            }  
        }

		window->display();
	}

	return 0;
}


