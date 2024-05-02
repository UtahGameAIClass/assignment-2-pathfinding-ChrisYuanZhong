#pragma once

#ifndef ASTAR_H
#define ASTAR_H

#include "DirectedWeightedGraph.h"
#include "TileMap.h"
#include <vector>

std::vector<DirectedWeightedEdge> AStar(const DirectedWeightedGraph& graph, int startNode, int endNode);
std::vector<Cell> AStar(const TileMap& map, Cell& start, Cell& goal, bool allowDiagonal = false);

#endif // ASTAR_H