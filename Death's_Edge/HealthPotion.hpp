#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP

#include "Item.hpp"

class HealthPotion : public Item {
public:
	HealthPotion(std::string name, int effect);

	void useItem(Character& character) override;

	~HealthPotion();
protected:
	int health, effect;
	std::string name;
};

#endif