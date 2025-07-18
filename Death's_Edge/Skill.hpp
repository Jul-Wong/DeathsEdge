#ifndef SKILL_HPP
#define SKILL_HPP

#include <string>
#include "Character.hpp"

enum class TargetType {
	Self,
	Enemy
};

class Skill {
public:
	Skill(std::string name, int manaCost, int damage, TargetType targetType);

	const std::string& getName() const;
	int getManaCost() const;
	int getDamage() const;
	TargetType getTargetType() const;

	void apply(Character& user, Character& target) const;

private:
	std::string name;
	int manaCost;
	int damage;
	TargetType targetType;
};

#endif 
