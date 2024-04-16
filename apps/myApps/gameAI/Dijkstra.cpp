#include "Dijkstra.h"
#include <set>

std::vector<DirectedWeightedEdge> Dijkstra(const DirectedWeightedGraph& graph, int startNode, int endNode)
{
	// Create a vector to store the shortest path
	std::vector<DirectedWeightedEdge> shortestPath;

	// Create a vector to store the distance to each node
	std::unordered_map<int, float> distance;

	// Create a vector to store the previous node in the shortest path
	std::unordered_map<int, int> previous;

	// Create a set to store the unvisited nodes
	std::set<int> unvisited;

	// Initialize the distance to each node to infinity
	for (auto& pair : graph.adjacencyList) {
		distance[pair.first] = std::numeric_limits<float>::infinity();
		unvisited.insert(pair.first);
	}

	// Set the distance to the start node to 0
	distance[startNode] = 0;

	// While there are unvisited nodes
	while (!unvisited.empty()) {
		// Find the unvisited node with the smallest distance
		int minNode = *unvisited.begin();
		for (int node : unvisited) {
			if (distance[node] < distance[minNode]) {
				minNode = node;
			}
		}

		// Remove the node from the unvisited set
		unvisited.erase(minNode);

		// Get the neighbors of the node
		auto neighbors = graph.getNeighbors(minNode);

		// For each neighbor of the node
		for (const DirectedWeightedEdge& edge : neighbors) {
			// Calculate the distance to the neighbor
			float dist = distance[minNode] + edge.weight;

			// If the new distance is shorter than the current distance
			if (dist < distance[edge.destination]) {
				// Update the distance
				distance[edge.destination] = dist;

				// Update the previous node
				previous[edge.destination] = minNode;
			}
		}
	}

	// Reconstruct the shortest path
	int currentNode = endNode;
	while (currentNode != startNode) {
		int prevNode = previous[currentNode];
		auto neighbors = graph.getNeighbors(prevNode);
		for (const DirectedWeightedEdge& edge : neighbors) {
			if (edge.destination == currentNode) {
				shortestPath.push_back(edge);
				break;
			}
		}
		currentNode = prevNode;
	}

	// Reverse the path
	std::reverse(shortestPath.begin(), shortestPath.end());

	return shortestPath;
}
