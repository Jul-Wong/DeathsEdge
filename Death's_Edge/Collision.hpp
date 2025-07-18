#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Collision {
public:
	static bool isMapColliding(const std::vector<std::vector<int>>& map, const sf::FloatRect& bounds, int tileSize);
	static bool isSpriteColliding(const sf::Sprite& a, const sf::Sprite& b);
};

#endif 
