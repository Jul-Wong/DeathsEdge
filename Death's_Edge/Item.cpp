#include <iostream>

#include "Item.hpp"

Item::Item(std::string name, int effect) : name(name), effect(effect) {};

std::string Item::getName() const {
    return name;
}

int Item::getEffect() const {
    return effect; 
}

Item::~Item() {};

