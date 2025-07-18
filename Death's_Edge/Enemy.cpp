#include "Enemy.hpp"



Enemy::Enemy(std::string name, int health, int mana, int attack, int resist, int experience)
    : Character(name, health, mana, attack, resist), experience(experience) {
};

int Enemy::getExperience() const {
    return experience;
}