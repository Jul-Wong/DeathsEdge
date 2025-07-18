#include <iostream>

#include "HealthPotion.hpp"

HealthPotion::HealthPotion(std::string name, int effect) : Item(name, effect) {};

void HealthPotion::useItem(Character& character) {
    character.setHealth(character.getHealth() + getEffect());
    std::cout << character.getName() << " uses " << getName() << " and gains " << getEffect() << " health." << std::endl;
}

HealthPotion::~HealthPotion() {};