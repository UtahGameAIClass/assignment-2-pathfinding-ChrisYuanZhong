#pragma once

#ifndef DIRECTED_WEIGHTED_GRAPH_H
#define DIRECTED_WEIGHTED_GRAPH_H

#include <vector>
#include <unordered_map>

// A simple struct to represent a node in a 2D plane
struct Node {
    // Coordinates
    float x;
    float y;

    // Constructor
    Node() : x(0), y(0) {}
    Node(float x, float y) : x(x), y(y) {}
};

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

    std::unordered_map<int, Node> nodes;

    void addNode(int id, Node node) {
        nodes[id] = node;
    }

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

    Node getNode(int id) const {
		return nodes.at(id);
	}
};

#endif // DIRECTED_WEIGHTED_GRAPH_H