#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Character.hpp"
#include "Item.hpp"

class Player : public Character {
public:
	Player(std::string name, int health, int mana, int attack, int resist);

	int getLevel() const;
	void setLevel(int level);
	int getExperience() const;
	void addExperience(int xp);
	int getExperienceToNextLevel() const;
	int getRemainingExperience() const;
	void levelUp();
	void addItem(Item *item);
	void useItem(int index);
	bool run();

protected:
	int level, experience, experienceToNextLevel;
	std::vector<Item*> items;


};

#endif