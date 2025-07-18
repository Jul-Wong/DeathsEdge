#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray map_vertices;
	sf::Texture map_tileset;
};






#endif