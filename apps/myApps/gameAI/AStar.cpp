#include "AStar.h"
#include <set>

float heuristic(const DirectedWeightedGraph& graph, int startNode, int endNode)
{
	return 2.0f;
}

std::vector<DirectedWeightedEdge> AStar(const DirectedWeightedGraph& graph, int startNode, int endNode)
{
    // Create a vector to store the shortest path
    std::vector<DirectedWeightedEdge> shortestPath;

    // Create a map to store the cost from start node to each node
    std::unordered_map<int, float> gScore;

    // Create a map to store the total cost from start to goal through each node
    std::unordered_map<int, float> fScore;

    // Create a map to store the previous node in the shortest path
    std::unordered_map<int, int> cameFrom;

    // Create a set to store the open set (nodes to be evaluated)
    std::set<int> openSet;

    // Initialize gScore and fScore to infinity
    for (auto& pair : graph.adjacencyList) {
        gScore[pair.first] = std::numeric_limits<float>::infinity();
        fScore[pair.first] = std::numeric_limits<float>::infinity();
    }

    // Set the gScore for the start node to 0 and fScore to the heuristic value
    gScore[startNode] = 0;
    fScore[startNode] = heuristic(graph, startNode, endNode);

    // Add the start node to the open set
    openSet.insert(startNode);

    // While the open set is not empty
    while (!openSet.empty()) {
        // Find the node in openSet with the lowest fScore value
        int currentNode = *openSet.begin();
        for (int node : openSet) {
            if (fScore[node] < fScore[currentNode]) {
                currentNode = node;
            }
        }

        // If the current node is the goal, reconstruct the path and return it
        if (currentNode == endNode) {
            while (cameFrom.find(currentNode) != cameFrom.end()) {
                int prevNode = cameFrom[currentNode];
                auto neighbors = graph.getNeighbors(prevNode);
                for (const DirectedWeightedEdge& edge : neighbors) {
                    if (edge.destination == currentNode) {
                        shortestPath.push_back(edge);
                        break;
                    }
                }
                currentNode = prevNode;
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        // Remove the current node from the open set
        openSet.erase(currentNode);

        // Get the neighbors of the current node
        auto neighbors = graph.getNeighbors(currentNode);

        // For each neighbor of the current node
        for (const DirectedWeightedEdge& edge : neighbors) {
            // Calculate the tentative gScore
            float tentativeGScore = gScore[currentNode] + edge.weight;

            // If the tentative gScore is less than the gScore for the neighbor
            if (tentativeGScore < gScore[edge.destination]) {
                // This path is the best so far, record it
                cameFrom[edge.destination] = currentNode;
                gScore[edge.destination] = tentativeGScore;
                fScore[edge.destination] = gScore[edge.destination] + heuristic(graph, edge.destination, endNode);

                // If the neighbor is not in openSet, add it
                if (openSet.find(edge.destination) == openSet.end()) {
                    openSet.insert(edge.destination);
                }
            }
        }
    }

    // If the goal was not reached, return an empty path
    return shortestPath;
}
