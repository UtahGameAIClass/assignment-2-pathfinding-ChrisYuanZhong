#include "TileMap.h"

TileMap::TileMap(int width, int height)
    : width(width), height(height), map(height, std::vector<bool>(width, false)) {}

bool TileMap::isObstacle(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return true; // Out of bounds, treat as obstacle
    }
    return map[y][x];
}

void TileMap::SetObstacle(int x, int y, bool obstacle)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
		map[y][x] = obstacle;
	}
}
