#include "Enemy.hpp"



Enemy::Enemy(std::string name, int health, int mana, int attack, int resist, int experience)
    : Character(name, health, mana, attack, resist), experience(experience) {
};

void Enemy::takeTurn(Character& player) {
    std::cout << name << " is taking their turn." << std::endl;
    std::cout << name << " has " << health << " health and " << mana << " mana." << std::endl;
    attack(player);
}

int Enemy::getExperience() const {
    return experience;
}