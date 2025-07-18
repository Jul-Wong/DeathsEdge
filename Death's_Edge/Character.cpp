#include <iostream>

#include "Character.hpp"

Character::Character(std::string name, int health, int mana, int attackPower, int resist) 
    : name(name), health(health), mana(mana), attackPower(attackPower), resist(resist), maxHealth(100), maxMana(100) {};

    bool Character::isAlive() const {
        return health > 0;
    }

    int Character::getHealth() const {
        return health;
    }

    void Character::setHealth(int health) {
        this->health = std::min(health, maxHealth);
    }

    std::string Character::getName() const {
        return name;
    }

    void Character::setName(std::string name) {
        this->name = name;
    }

    int Character::getAttack() const {
        return attackPower;
    }

    void Character::setAttack(int attack) {
        this->attackPower = attack;
    }

    int Character::getResist() const {
        return resist;
    }

    void Character::setResist(int resist) {
        this->resist = resist;
    }

    int Character::getMana() const {
        return mana;
    }

    void Character::setMana(int mana) {
        this->mana = mana;
    }

    int Character::getMaxHealth() const {
        return maxHealth;
    }

    void Character::setMaxHealth(int maxHealth) {
        this->maxHealth = maxHealth;
    }

    int Character::getMaxMana() const {
        return maxMana;
    }

    void Character::setMaxMana(int maxMana) {
        this->maxMana = maxMana;
    }

    std::string Character::getSpritePath()
    {
        return spritePath;
    }


    void Character::setSpritePath(std::string spritePath) {
        this->spritePath = spritePath;
    }

    void Character::attack(Character& target) {
        int damage = std::max(0, attackPower - target.resist);
        target.health -= damage;
        std::cout << name << " attacks " << target.name << " for " << damage << " damage." << std::endl;
    }

    Character::~Character() {};