#pragma once

#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>

// Define the structure for grid cell
struct Cell {
    int x, y;

    Cell() : x(0), y(0) {}
    Cell(int x, int y) : x(x), y(y) {}

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Cell& other) const {
		return !(*this == other);
	}

    bool operator<(const Cell& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

    bool operator>(const Cell& other) const {
    	return x > other.x || (x == other.x && y > other.y);
    }
};

// Define the hash function for unordered_set
namespace std {
    template <>
    struct hash<Cell> {
        size_t operator()(const Cell& c) const {
            return hash<int>()(c.x) ^ hash<int>()(c.y);
        }
    };
}

class TileMap {
public:
    TileMap(int width, int height);
    bool isObstacle(int x, int y) const;
    void SetObstacle(int x, int y, bool obstacle);
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    float GetTileSize() const { return tileSize; }
    float SetTileSize(float size) { tileSize = size; }

    float GetxPosition(int x) const { return x * tileSize; }
    float GetyPosition(int y) const { return y * tileSize; }
    int GetxIndex(float x) const { return x / tileSize; }
    int GetyIndex(float y) const { return y / tileSize; }

private:
    int width, height;
    float tileSize = 10;
    std::vector<std::vector<bool>> map;
};

#endif // TILE_MAP_H