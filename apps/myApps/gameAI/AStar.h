#pragma once

#ifndef ASTAR_H
#define ASTAR_H

#include "DirectedWeightedGraph.h"
#include <vector>

std::vector<DirectedWeightedEdge> AStar(const DirectedWeightedGraph& graph, int startNode, int endNode);

#endif // ASTAR_H