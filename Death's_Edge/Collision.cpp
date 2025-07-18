#include "Collision.hpp"

bool Collision::isMapColliding(const std::vector<std::vector<int>>& map, const sf::FloatRect& bounds, int tileSize) {
    int startX = static_cast<int>(bounds.position.x) / tileSize;
    int endX = static_cast<int>(bounds.position.x + bounds.size.x) / tileSize;
    int startY = static_cast<int>(bounds.position.y) / tileSize;
    int endY = static_cast<int>(bounds.position.y + bounds.size.y) / tileSize;
    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            if (y >= 0 && y < static_cast<int>(map.size()) &&
                x >= 0 && x < static_cast<int>(map[0].size())) {

                int tileID = map[y][x];

                // Assuming walkable tiles: 0-15 (floor); unwalkable: 16+ (walls)
                if (tileID >= 16) {
                    return true; // collision
                }
            }
        }
    }

    return false; 
}

bool Collision::isSpriteColliding(const sf::Sprite& a, const sf::Sprite& b) {
        sf::FloatRect rectA = a.getGlobalBounds();
        sf::FloatRect rectB = b.getGlobalBounds();
    return (rectA.position.x < rectB.position.x + rectB.size.x && 
        rectA.position.x + rectA.size.x > rectB.position.x && 
        rectA.position.y < rectB.position.y + rectB.size.y && 
        rectA.position.y + rectA.size.y > rectB.position.y);
}
