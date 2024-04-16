#pragma once

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "DirectedWeightedGraph.h"
#include <vector>

std::vector<DirectedWeightedEdge> Dijkstra(const DirectedWeightedGraph& graph, int startNode, int endNode);

#endif // DIJKSTRA_H