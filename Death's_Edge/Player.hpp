#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Character.hpp"
#include "Item.hpp"
#include "Skill.hpp"

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

	void addSkill(Skill* skill);

	void equipItem(Item* item, int slot);
	void equipSkill(Skill* skill, int slot);
	
	std::vector<Item*> getEquippedItems() const;
	std::vector<Skill*> getEquippedSkills() const;



protected:
	int level, experience, experienceToNextLevel;
	std::vector<Item*> items;

private:
	std::vector<Item*> inventoryItems;
	std::vector<Skill*> inventorySkills;

	Item* equippedItems[3] = { nullptr, nullptr, nullptr };
	Skill* equippedSkills[3] = { nullptr, nullptr, nullptr };


};

#endif