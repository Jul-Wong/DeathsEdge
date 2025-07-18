#include "Skill.hpp"
#include <iostream>

Skill::Skill(std::string name, int manaCost, int damage, TargetType targetType) 
	: name(name), manaCost(manaCost), damage(damage), targetType(targetType) {
}

const std::string& Skill::getName() const {
	return name;
}
int Skill::getManaCost() const {
	return manaCost;
}
int Skill::getDamage() const {
	return damage;
}
TargetType Skill::getTargetType() const {
	return targetType;
}

void Skill::apply(Character& user, Character& target) const {
	if (user.getMana() < manaCost) {
		std::cout << "Not enough mana to use " << name << "!" << std::endl;
		return;
	}
	user.setMana(user.getMana() - manaCost);
	if (targetType == TargetType::Enemy) {
		target.setHealth(target.getHealth() - damage);
		std::cout << user.getName() << " uses " << name << " on " << target.getName() 
				  << ", dealing " << damage << " damage!" << std::endl;
	} else if (targetType == TargetType::Self) {
		user.setHealth(user.getHealth() + damage);
		std::cout << user.getName() << " uses " << name 
				  << ", healing for " << damage << " health!" << std::endl;
	}
}
