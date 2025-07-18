#include "Player.hpp"

/**
* @brief Player constructor initializes a Player object with given attributes.
* @param name The name of the player.
* @param health The initial health of the player.
* @param mana The initial mana of the player.
* @param attack The initial attack power of the player.
* @param resist The initial resistance of the player.
* This constructor also initializes the player's inital level, experience, and experience required for the next level.
* It calls the base class Character constructor to set the common attributes.
* @details The Player class inherits from Character and adds functionality for leveling up, gaining experience, and managing items.
*/
Player::Player(std::string name, int health, int mana, int attack, int resist)
        : Character(name, health, mana, attack, resist), level(1), experience(0), experienceToNextLevel(100) {} ;

/**
* @brief Gets the current level of the player.
* @return The current level of the player.
*/
int Player::getLevel() const {
    return level;
}

/**
* @brief Sets the level of the player.
* @param level The new level to set for the player
*/
void Player::setLevel(int level) {
    this->level = level;
}

/**
* @brief Gets the current experience of the player.
* @return The current experience points of the player.
*/
int Player::getExperience() const {
    return experience;
}

/**
* @brief Gets the experience required for the next level.
* @return The experience points required to reach the next level.
*/
int Player::getExperienceToNextLevel() const {
    return experienceToNextLevel;
}

/**
* @brief Gets the remaining experience needed to reach the next level.
* @return The amount of experience points still needed to level up.
*/
int Player::getRemainingExperience() const {
    return experienceToNextLevel - experience;
}

/** * @brief Adds experience points to the player.
 * @param xp The amount of experience points to add.
 * If the player's experience exceeds the threshold for leveling up, it calls levelUp().
 */
void Player::addExperience(int xp) {
    this->experience += xp;
    if (experience >= experienceToNextLevel) {
        levelUp();
    }
}

/**
* @brief Levels up the player, increasing their attributes and resetting experience.
* This function increases the player's level, health, mana, attack power, and resistance.
* It also increases the experience required for the next level.
*/
void Player::levelUp() {
    level++;
    health += 10; // levelUpBonusHealth
    mana += 10;   // levelUpBonusMana
    attackPower += 2; // levelUpBonusAttack
    resist += 1;  // levelUpBonusResist
    experienceToNextLevel += 50;
    std::cout << name << " leveled up to level " << level << "!" << std::endl;
}

/**
* @brief Adds an item to the player's inventory.
* @param item Pointer to the Item object to be added.
*/
void Player::addItem(Item* item) {
    items.push_back(item);
}

/**
* @brief Uses an item from the player's inventory.
* @param index The index of the item in the inventory to be used.
*/
void Player::useItem(int index) {
    if (index >= 0 && index < items.size()) {
        items[index]->useItem(*this);
        items.erase(items.begin() + index);
        std::cout << "Item used." << std::endl;
    }
    else {
        std::cout << "Invalid number. Please try again." << std::endl;
    }
}

/**
* @brief Attempts to run away from combat.
* @return True if the player successfully runs away, false otherwise.
* If the run is unsuccessful, the player takes 10 damage.
* This simulates a chance-based escape mechanic.
*/
bool Player::run() {
    std::cout << "You attempt to run away!" << std::endl;
    if (rand() % 2 == 0) {
        std::cout << "You successfully run away!" << std::endl;
        return true;
    } else {
        std::cout << "You failed to run away!" << std::endl;
        health -= 10;
        return false;
    }
}
