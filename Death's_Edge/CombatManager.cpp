#include "CombatManager.hpp"
#include <iostream>

std::string fontPath = "Fonts/trebuc.ttf";
std::string playerStatPath = "Sprites/Player_Stats.png";
int profileHeight = 330;


CombatManager::CombatManager(Player* player, Enemy* enemy) : player(player), enemy(enemy), currentPhase(TurnPhase::PlayerTurn),
isCombatOver(false), combatText(font, "Combat Starts!", 24),
button1(font, "ATTACK", 30), button2(font, "ITEMS", 30), button3(font, "SKILL", 30), button4(font, "RUN", 30), itemPage(false), skillPage(false)  {
	if (!font.openFromFile(fontPath)) {
		std::cerr << "Failed to load " << fontPath << std::endl;
		outcome = CombatOutcome::PlayerDefeat;
		return;
	}

	combatText = sf::Text(font, "Combat Starts!", 24);
	combatText.setFillColor(sf::Color::White);
	combatText.setPosition(sf::Vector2f(100.f, 100.f));

	button1.setPosition(sf::Vector2f(1200, 800));
	button1.setFillColour(sf::Color(200, 100, 100, 255));
	button1.setHoverColour(sf::Color(250, 150, 150));
	button1.setTextColour(sf::Color(50, 0, 0), sf::Color(255, 0, 0), 1.0f);

	button2.setPosition(sf::Vector2f(1550, 800));
	button2.setFillColour(sf::Color(100, 100, 200, 255));
	button2.setHoverColour(sf::Color(150, 150, 250, 255));
	button2.setTextColour(sf::Color(0, 0, 50), sf::Color(0, 0, 255), 1.0f);

	button3.setPosition(sf::Vector2f(1200, 950));
	button3.setFillColour(sf::Color(100, 200, 100, 255));
	button3.setHoverColour(sf::Color(150, 250, 150, 255));
	button3.setTextColour(sf::Color(0, 50, 0), sf::Color(0, 255, 0), 1.0f);

	button4.setPosition(sf::Vector2f(1550, 950));
	button4.setFillColour(sf::Color(225, 165, 0, 255));
	button4.setHoverColour(sf::Color(150, 250, 150, 255));
	button4.setTextColour(sf::Color(50, 25, 0), sf::Color(255, 170, 0), 1.0f);
	

}

CombatOutcome CombatManager::combatStatus(sf::RenderWindow& window) {
	handleInput(window);
	render(window);
	return outcome;
}

void CombatManager::handleInput(sf::RenderWindow& window) {
	static bool mouseHandled = false;
	sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	// Item and Skill Page
	if (itemPage || skillPage) {
		if (itemPage) {
			button1.setText("ITEM 1");
			button2.setText("ITEM 2");
			button3.setText("ITEM 3");
			button4.setText("BACK");
		}

		if (skillPage) {
			button1.setText("SKILL 1");
			button2.setText("SKILL 2");
			button3.setText("SKILL 3");
			button4.setText("BACK");
		}

	}
	else {
		button1.setText("ATTACK");
		button2.setText("ITEMS");
		button3.setText("SKILLS");
		button4.setText("RUN");

	}

	// Hover Feedback
	button1.hoverFeedback(window);
	button2.hoverFeedback(window);
	button3.hoverFeedback(window);
	button4.hoverFeedback(window);

	if (!enemy->isAlive()) {
		std::cout << "Enemy defeated! Awarding XP: " << enemy->getExperience() << std::endl;
		player->addExperience(enemy->getExperience());
		outcome = CombatOutcome::PlayerVictory;
		return;
	} else if (!player->isAlive()) {
		outcome = CombatOutcome::PlayerDefeat;
		return;
	}

	if (currentPhase == TurnPhase::PlayerTurn && !mouseHandled && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (itemPage) {
			if (button1.isClicked(window)) player->useItem(0);
			else if (button2.isClicked(window)) player->useItem(1);
			else if (button3.isClicked(window)) player->useItem(2);
			else if (button4.isClicked(window)) itemPage = false;
			currentPhase = TurnPhase::EnemyWaiting;
			turnClock.restart();
		}
		else if (skillPage) {
			if (button1.isClicked(window)) player->useSkill(1);
			else if (button2.isClicked(window)) player->useSkill(2);
			else if (button3.isClicked(window)) player->useSkill(3);
			else if (button4.isClicked(window)) skillPage = false;
			currentPhase = TurnPhase::EnemyWaiting;
			turnClock.restart();
		}
		else {
			if (button1.isClicked(window)) {
				player->attack(*enemy);
				currentPhase = TurnPhase::EnemyWaiting;
				turnClock.restart();
			}
			else if (button2.isClicked(window)) {
				itemPage = true;
			}
			else if (button3.isClicked(window)) {
				skillPage = true;
			}
			else if (button4.isClicked(window)) {
				if (player->run()) {
					outcome = CombatOutcome::RunSuccess;
				}
				else {
					currentPhase = TurnPhase::EnemyWaiting;
					turnClock.restart();
				}
			}
		}

		mouseHandled = true;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		mouseHandled = false;
	}

	// --- ENEMY DELAY PHASE ---
	if (currentPhase == TurnPhase::EnemyWaiting && turnClock.getElapsedTime().asSeconds() > enemyDelay) {
		currentPhase = TurnPhase::EnemyTurn;
	}

	// --- ENEMY ACTION ---
	if (currentPhase == TurnPhase::EnemyTurn) {
		enemy->attack(*player);
		if (!player->isAlive()) {
			outcome = CombatOutcome::PlayerDefeat;
			return;
		}
		currentPhase = TurnPhase::PlayerTurn;
	}
}

void CombatManager::render(sf::RenderWindow& window) {
	std::string status =
		player->getName() + " HP: " + std::to_string(player->getHealth()) + "\n" +
		enemy->getName() + " HP: " + std::to_string(enemy->getHealth()) + "\n\n";

	combatText.setString(status);



	// Player Stat Bar
	sf::Texture playerStat;
	
	if (!playerStat.loadFromFile(playerStatPath)) {
		std::cerr << "ERROR: CANNOT LOAD FILE::" << playerStatPath << std::endl;
		return;
	}

	sf::Sprite playerStatBar(playerStat);

	playerStatBar.setPosition(sf::Vector2f(0, 800));
	playerStatBar.setScale(sf::Vector2f(0.25, 0.25));


	// Health Bar
	float hpPercent = static_cast<float>(player->getHealth()) / player->getMaxHealth();
	sf::RectangleShape hpFront(sf::Vector2f(167 * hpPercent, 13));
	hpFront.setFillColor(sf::Color::Red);
	hpFront.setPosition(sf::Vector2f(145, 850));

	// Mana Bar
	float manaPercent = static_cast<float>(player->getMana()) / player->getMaxMana();
	sf::RectangleShape manaFront(sf::Vector2f(167 * manaPercent, 13));
	manaFront.setFillColor(sf::Color::Blue);
	manaFront.setPosition(sf::Vector2f(145, 885));

	// Experience Bar
	float xpPercent = static_cast<float>(player->getExperience()) / player->getExperienceToNextLevel();
	sf::RectangleShape xpFront(sf::Vector2f(167 * xpPercent, 13));
	xpFront.setFillColor(sf::Color::Green);
	xpFront.setPosition(sf::Vector2f(145, 920));

	sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, profileHeight));
	rectangle.setFillColor(sf::Color(20, 20, 20));
	rectangle.setPosition(sf::Vector2f(0, window.getSize().y - profileHeight));

	sf::CircleShape stand(100.f);
	stand.setScale(sf::Vector2f(2.5, 1));
	stand.setFillColor(sf::Color(211, 211, 211, 200));
	stand.setOrigin(stand.getGeometricCenter());
	stand.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - profileHeight - 300));
	stand.setOutlineThickness(3.0f);
	stand.setOutlineColor(sf::Color::Black);

	sf::Texture enemyCombat;
	if (!enemyCombat.loadFromFile(enemy->getSpritePath())) {
		std::cerr << "ERROR:: COULD NOT LOAD FILE:: " << enemy->getSpritePath() << std::endl;
		return;
	}
	sf::Sprite enemySpriteCombat(enemyCombat);
	enemySpriteCombat.setScale(sf::Vector2f(5, 5));
	sf::IntRect dir[4];
	for (int i = 0; i < 4; i++) {
		dir[i] = sf::IntRect(sf::Vector2i(32 * i, 0), sf::Vector2i(32, 32));
	}
	enemySpriteCombat.setTextureRect(dir[0]);
	enemySpriteCombat.setPosition(sf::Vector2f(window.getSize().x / 2 - 80, window.getSize().y - profileHeight - 400));

	
	window.clear(sf::Color(28, 20, 2));
	window.draw(stand);
	window.draw(playerStatBar);
	window.draw(hpFront);
	window.draw(manaFront);
	window.draw(xpFront);
	window.draw(enemySpriteCombat);
	button1.draw(window);
	button2.draw(window);
	button3.draw(window);
	button4.draw(window);
	window.draw(combatText);
}
