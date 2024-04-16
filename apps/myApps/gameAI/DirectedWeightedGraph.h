#pragma once

#ifndef DIRECTED_WEIGHTED_GRAPH_H
#define DIRECTED_WEIGHTED_GRAPH_H

#include <vector>
#include <unordered_map>

// Define the DirectedWeightedEdge structure
struct DirectedWeightedEdge {
    int source;
    int destination;
    float weight;

    DirectedWeightedEdge(int source, int destination, float weight)
        : source(source), destination(destination), weight(weight) {}
};

// Define the DirectedWeightedGraph class
class DirectedWeightedGraph {
public:
    // Use an adjacency list to represent the graph
    std::unordered_map<int, std::vector<DirectedWeightedEdge>> adjacencyList;

    // Method to add an edge to the graph
    void addEdge(DirectedWeightedEdge edge) {
        adjacencyList[edge.source].push_back(edge);
    }

    // Method to get the neighbors of a node
    std::vector<DirectedWeightedEdge> getNeighbors(int node) const {
        auto it = adjacencyList.find(node);
        if (it != adjacencyList.end()) {
            return it->second;
        }
        return {};
    }
};

#endif // DIRECTED_WEIGHTED_GRAPH_H