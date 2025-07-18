#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "Character.hpp"

class Item {
public:
	Item(std::string name, int effect);
	virtual void useItem(Character& character) {};

	std::string getName() const;
	int getEffect() const;
	virtual ~Item();

protected:
	std::string name;
	int effect;
};


#endif