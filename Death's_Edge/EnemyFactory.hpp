#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

#include "Enemy.hpp"
#include <string>


class EnemyFactory {
public:
	static Enemy* create(const std::string& type);
	static Enemy* createRandom();

};

#endif 