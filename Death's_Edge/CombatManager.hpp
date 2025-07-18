#ifndef COMBATMANAGER_HPP
#define COMBATMANAGER_HPP

#include "Player.hpp"
#include "Enemy.hpp"
#include "HealthPotion.hpp"
#include "CombatButton.hpp"
#include <SFML/Graphics.hpp>

enum class TurnPhase {
	PlayerTurn,
	EnemyWaiting,
	EnemyTurn,
	Transisiton
};

enum class CombatOutcome {
	Ongoing,
	PlayerVictory,
	PlayerDefeat,
	RunSuccess
};

class CombatManager {
public:
	CombatManager(Player* player, Enemy* enemy);
	CombatOutcome combatStatus(sf::RenderWindow& window); // Returns true when Combat is Over

private:
	Player* player;
	Enemy* enemy;

	sf::Clock turnClock;
	float enemyDelay = 0.5f;
	TurnPhase currentPhase;

	bool isCombatOver;
	bool itemPage, skillPage;

	sf::Font font;
	sf::Text combatText;

	CombatButton button1, button2, button3, button4;
	CombatOutcome outcome = CombatOutcome::Ongoing;

	void handleInput(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};

#endif