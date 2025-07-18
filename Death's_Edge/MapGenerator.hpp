#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include <vector>
#include <utility>

struct Room {
	int x, y, width, height;
};

struct GeneratedMap {
	std::vector<std::vector<int>> tiles;
	std::vector<Room> rooms;
};

class MapGenerator {
public:
	static GeneratedMap generateBSPMap(int width, int height, int maxDepth = 4);

};


#endif
