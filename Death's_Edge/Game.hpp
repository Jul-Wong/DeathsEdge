#ifndef GAME_HPP
#define GAME_HPP

#include "Character.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "HealthPotion.hpp"

class Game {
public:
	Game(std::string playerName);
	void start();
	~Game();
protected:
	Player* player;
	Enemy* enemy;
	bool isRunning;
    std::vector<std::string> enemyNames = { "Goblin", "Skeleton",
"Not A Mimic", "The Elusive Pink Slime", "Herald The Great" };
    std::vector<int> enemyHealth = { 20, 35, 45, 30, 55 };
    std::vector<int> enemyAttack = { 5, 7, 9, 6, 11 };
    std::vector<int> enemyResist = { 2, 3, 4, 2, 5 };
    std::vector<int> enemyMana = { 10, 15, 20, 12, 25 };
    std::vector<int> enemyXP = { 15, 25, 45, 30, 55 };

    std::vector<std::string> bossNames = { "Bruce", "Maybelline" };
    std::vector<int> bossHealth = { 40, 60 };
    std::vector<int> bossAttack = { 8, 15 };
    std::vector<int> bossResist = { 6 , 9 };
    std::vector<int> bossMana = { 15, 25 };

	Enemy* generateEnemy();
};

#endif