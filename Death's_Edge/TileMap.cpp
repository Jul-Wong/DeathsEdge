#include "TileMap.hpp"

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles) {
    int map_width = static_cast<int>(tiles[0].size());
    int map_height = static_cast<int>(tiles.size());

    if (!map_tileset.loadFromFile(tileset)) {
        return false;
    }

    map_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    map_vertices.resize(map_width * map_height * 6); // 6 vertices per tile (2 triangles)

    for (int y = 0; y < map_height; ++y) {
        for (int x = 0; x < map_width; ++x) {
            int tileNumber = tiles[y][x];

            int tu = tileNumber % (map_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (map_tileset.getSize().x / tileSize.x);

            float px = static_cast<float>(x * tileSize.x);
            float py = static_cast<float>(y * tileSize.y);

            float tx = static_cast<float>(tu * tileSize.x);
            float ty = static_cast<float>(tv * tileSize.y);

            sf::Vertex* tri = &map_vertices[(x + y * map_width) * 6];

            // Triangle 1
            tri[0].position = { px, py };
            tri[1].position = { px + tileSize.x, py };
            tri[2].position = { px + tileSize.x, py + tileSize.y };

            tri[0].texCoords = { tx, ty };
            tri[1].texCoords = { tx + tileSize.x, ty };
            tri[2].texCoords = { tx + tileSize.x, ty + tileSize.y };

            // Triangle 2
            tri[3].position = { px, py };
            tri[4].position = { px + tileSize.x, py + tileSize.y };
            tri[5].position = { px, py + tileSize.y };

            tri[3].texCoords = { tx, ty };
            tri[4].texCoords = { tx + tileSize.x, ty + tileSize.y };
            tri[5].texCoords = { tx, ty + tileSize.y };
        }
    }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &map_tileset;
    target.draw(map_vertices, states);
}
