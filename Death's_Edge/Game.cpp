#include "Game.hpp"

Game::Game(std::string playerName) {
        player = new Player(playerName, 100, 100, 10, 5);
        player->addItem(new HealthPotion("Health Potion", 20));
        player->addItem(new HealthPotion("Health Potion", 20));
        player->addItem(new HealthPotion("Health Potion", 20));
        enemy = generateEnemy();
    }

    void Game::start() {
        isRunning = true;
    }

    Enemy* Game::generateEnemy() {
        int randomIndex = rand() % enemyNames.size();
        Enemy* enemy = new Enemy(enemyNames[randomIndex], enemyHealth[randomIndex],
            enemyMana[randomIndex], enemyAttack[randomIndex], enemyResist[randomIndex], enemyXP[randomIndex]);
        return enemy;
    }

    Game::~Game() {
        delete player;
        delete enemy;
    }