#include "Player.hpp"

Player::Player(std::string name, int health, int mana, int attack, int resist)
        : Character(name, health, mana, attack, resist), level(1), experience(0), experienceToNextLevel(100) {} ;

int Player::getLevel() const {
    return level;
}

void Player::setLevel(int level) {
    this->level = level;
}

int Player::getExperience() const {
    return experience;
}

int Player::getExperienceToNextLevel() const {
    return experienceToNextLevel;
}

int Player::getRemainingExperience() const {
	return experienceToNextLevel - experience;
}

void Player::addExperience(int xp) {
    this->experience += xp;
    if (experience >= experienceToNextLevel) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    health += 10; // levelUpBonusHealth
    mana += 10;   // levelUpBonusMana
    attackPower += 2; // levelUpBonusAttack
    resist += 1;  // levelUpBonusResist
    experienceToNextLevel += 50;
    std::cout << name << " leveled up to level " << level << "!" << std::endl;
}

void Player::addItem(Item* item) {
    items.push_back(item);
}

void Player::useItem(int index) {
    if (index >= 0 && index < items.size()) {
        items[index]->useItem(*this);
        items.erase(items.begin() + index);
        std::cout << "Item used." << std::endl;
    } else {
        std::cout << "Invalid number. Please try again." << std::endl;
    }
}

void Player::useSkill(int skillIndex) {
    switch (skillIndex) {
    case 1:
        
        std::cout << "You use Fireball and deal 10 damage to the enemy." << std::endl;
        mana -= 10;
        break;
    case 2:
        std::cout << "You use Heal and gain 10 health." << std::endl;
        mana -= 10;
        health += 10;
        break;
    case 3:
        std::cout << "You use Shield and gain 10 mana." << std::endl;
        mana += 10;
        break;
    default:
        std::cout << "Invalid skill. Please try again." << std::endl;
        break;
    }

}

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

void Player::takeTurn(Character& enemy) {
    bool turnEnded = false;
    bool runSuccess = false;

    while (!turnEnded) {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "You are taking your turn." << std::endl;
        std::cout << "Health: " << health << " Mana: " << mana << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Use Item" << std::endl;
        std::cout << "3. Use Skill" << std::endl;
        std::cout << "4. Run" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (!checkSelection(choice, 1, 4)) {
            continue;
        }

        switch (choice) {
        case 1:
            attack(enemy);
            turnEnded = true;
            break;
        case 2:
            std::cout << "You have the following items:" << std::endl;
            for (int i = 0; i < items.size(); i++) {
                std::cout << i << ". " << items[i]->getName() << std::endl;
            }
            std::cout << "Enter the number of the item you want to use: ";
            int itemIndex;
            std::cin >> itemIndex;

            if (!checkSelection(itemIndex, 0, static_cast<int>(items.size()))) {
                continue;
            }

            useItem(itemIndex);
            break;
        case 3:
            std::cout << "You have the following skills:" << std::endl;
            std::cout << "1. Fireball" << std::endl;
            std::cout << "2. Heal" << std::endl;
            std::cout << "3. Shield" << std::endl;
            std::cout << "Enter the number of the skill you want to use: ";
            int skillIndex;
            std::cin >> skillIndex;

            if (!checkSelection(skillIndex, 1, 3)) {
                continue;
            }
            useSkill(skillIndex);
            turnEnded = true;
            break;
        case 4:
            if (run()) {
                turnEnded = true;
                runSuccess = true;
                break;
            } else {
                continue;
            }
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        if (runSuccess) {
            enemy.setHealth(0);
            break;
        } else {
            turnEnded = true;
        }
    }
    std::cout << "--------------------------------" << std::endl;

}

bool Player::checkSelection(int choice, int minChoice, int maxChoice) {
    if (std::cin.fail()) {
        std::cin.clear(); // clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
        std::cout << "Invalid input. Try again." << std::endl;
        return false;
    }
    if (std::cin.eof()) {
        std::cout << "Input stream closed. Exiting..." << std::endl;
        return false;
    }

    // Validate choice
    if (choice < minChoice || choice > maxChoice) {
        std::cout << "Invalid choice. Please try again." << std::endl;
        return false;
    }
    return true;
}