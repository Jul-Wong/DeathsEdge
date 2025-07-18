#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#define MAX_HEALTH 100
#define MAX_MANA 100

class Character {
public:
	Character(std::string name, int health, int mana, int attackPower, int resist);
	virtual void takeTurn(Character &enemy) = 0;
	bool isAlive() const;
	void attack(Character &target);
	virtual ~Character();

	int getHealth() const;
	void setHealth(int health);
	std::string getName() const;
	void setName(std::string name);
	int getAttack() const;
	void setAttack(int attack);
	int getResist() const;
	void setResist(int resist);
	int getMana() const;
	void setMana(int mana);
	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);
	int getMaxMana() const;
	void setMaxMana(int maxMana);
	std::string getSpritePath();
	void setSpritePath(std::string spritePath);


protected:
	std::string name, spritePath;
	int health, mana, attackPower, resist, maxHealth, maxMana;

};



#endif