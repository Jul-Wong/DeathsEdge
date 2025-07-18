#include "MapGenerator.hpp"
#include <random>
#include <algorithm>

constexpr int VOID_TILE = 24;
constexpr int FLOOR_MIN = 0;
constexpr int FLOOR_MAX = 15;
constexpr int WALL_MIN = 16;
constexpr int WALL_MAX = 20;
constexpr int WALL_LIGHT_MIN = 21;
constexpr int WALL_LIGHT_MAX = 23;

static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> floorDist(FLOOR_MIN, FLOOR_MAX);
static std::uniform_int_distribution<int> wallDist(WALL_MIN, WALL_MAX);

void fillRoom(std::vector<std::vector<int>>& map, const Room& room) {
    for (int y = room.y; y < room.y + room.height; ++y) {
        for (int x = room.x; x < room.x + room.width; ++x) {
            map[y][x] = floorDist(rng);
        }
    }

    for (int y = room.y - 1; y <= room.y + room.height; ++y) {
        for (int x = room.x - 1; x <= room.x + room.width; ++x) {
            if (y >= 0 && y < map.size() && x >= 0 && x < map[0].size()) {
                if (map[y][x] == VOID_TILE) {
                    map[y][x] = wallDist(rng);
                }
            }
        }
    }
}

void carveCorridor(std::vector<std::vector<int>>& map, int x1, int y1, int x2, int y2) {
    // First move horizontally, then vertically (L-shaped)
    if (rng() % 2 == 0) {
        // Horizontal first
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
            for (int dy = 0; dy < 2; ++dy) {
                if (y1 + dy < map.size() && x < map[0].size())
                    map[y1 + dy][x] = floorDist(rng);
            }
        }
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
            for (int dx = 0; dx < 2; ++dx) {
                if (x2 + dx < map[0].size() && y < map.size())
                    map[y][x2 + dx] = floorDist(rng);
            }
        }
    }
    else {
        // Vertical first
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
            for (int dx = 0; dx < 2; ++dx) {
                if (x1 + dx < map[0].size() && y < map.size())
                    map[y][x1 + dx] = floorDist(rng);
            }
        }
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
            for (int dy = 0; dy < 2; ++dy) {
                if (y2 + dy < map.size() && x < map[0].size())
                    map[y2 + dy][x] = floorDist(rng);
            }
        }
    }
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[0].size(); ++x) {
            if (map[y][x] >= FLOOR_MIN && map[y][x] <= FLOOR_MAX) {
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        int nx = x + dx, ny = y + dy;
                        if (ny >= 0 && ny < map.size() && nx >= 0 && nx < map[0].size()) {
                            if (map[ny][nx] == VOID_TILE) {
                                map[ny][nx] = wallDist(rng);
                            }
                        }
                    }
                }
            }
        }
    }
}

Room bsp(std::vector<std::vector<int>>& map, std::vector<Room>& rooms, int x, int y, int width, int height, int depth, int maxDepth) {
    if (width < 12 || height < 12 || depth >= maxDepth) {
        int roomWidth = 4 + rng() % std::max(1, width - 6);
        int roomHeight = 4 + rng() % std::max(1, height - 6);
        int roomX = x + 1 + rng() % std::max(1, width - roomWidth - 2);
        int roomY = y + 1 + rng() % std::max(1, height - roomHeight - 2);
        
        Room room = { roomX, roomY, roomWidth, roomHeight };
        fillRoom(map, room);
        rooms.push_back(room);
        return room;
    }

    bool horizontalSplit = (width > height);

    if (horizontalSplit) {
        int split = 6 + rng() % std::max(1, width - 12);
        Room leftRoom = bsp(map, rooms, x, y, split, height, depth + 1, maxDepth);
        Room rightRoom = bsp(map, rooms, x + split, y, width - split, height, depth + 1, maxDepth);

        int x1 = leftRoom.x + leftRoom.width / 2;
        int y1 = leftRoom.y + leftRoom.height / 2;
        int x2 = rightRoom.x + rightRoom.width / 2;
        int y2 = rightRoom.y + rightRoom.height / 2;

        carveCorridor(map, x1, y1, x2, y2);
        return leftRoom;
    }
    else {
        int split = 6 + rng() % std::max(1, height - 12);
        Room topRoom = bsp(map, rooms, x, y, width, split, depth + 1, maxDepth);
        Room bottomRoom = bsp(map, rooms, x, y + split, width, height - split, depth + 1, maxDepth);
        
        int x1 = topRoom.x + topRoom.width / 2;
        int y1 = topRoom.y + topRoom.height / 2;
        int x2 = bottomRoom.x + bottomRoom.width / 2;
        int y2 = bottomRoom.y + bottomRoom.height / 2;
        
        carveCorridor(map, x1, y1, x2, y2);
        return topRoom;
    }
}

GeneratedMap MapGenerator::generateBSPMap(int width, int height, int maxDepth) {
    GeneratedMap result;
    result.tiles = std::vector<std::vector<int>>(height, std::vector<int>(width, VOID_TILE));
    bsp(result.tiles, result.rooms, 1, 1, width - 2, height - 2, 0, maxDepth);
    return result;
}
