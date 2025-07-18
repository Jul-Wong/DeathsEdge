#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>

#include "Character.hpp"

class Enemy : public Character {
public:
	Enemy(std::string name, int health, int mana, int attack, int resist, int experience);
	void takeTurn(Character& player) override;
	int getExperience() const;
protected:
	int experience = 0;
};

#endif