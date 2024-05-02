#include "AStar.h"
#include <queue>
#include <unordered_set>
#include <set>

float ConstantCost(const DirectedWeightedGraph& graph, int startNode, int endNode)
{
	return 0.0f;
}

float EuclideanDistance(const DirectedWeightedGraph& graph, int startNode, int endNode)
{
    float dx = graph.getNode(endNode).x - graph.getNode(startNode).x;
    float dy = graph.getNode(endNode).y - graph.getNode(startNode).y;
    return sqrt(dx * dx + dy * dy);
}

float heuristic(const DirectedWeightedGraph& graph, int startNode, int endNode)
{
    //return ConstantCost(graph, startNode, endNode);
    return EuclideanDistance(graph, startNode, endNode);
}

float heuristic(Cell& start, Cell& end) {
    return sqrt(pow(start.x - end.x, 2) + std::pow(start.y - end.y, 2));
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

std::vector<Cell> AStar(const TileMap& map, Cell& start, Cell& goal, bool allowDiagonal)
{
    // Create a vector to store the shortest path
	std::vector<Cell> shortestPath;

	// Create a set to store the open set (nodes to be evaluated)
	std::set<Cell> openSet;

	// Create a set to store the closed set (nodes already evaluated)
	std::set<Cell> closedSet;

	// Create a map to store the cost from start node to each node
	std::unordered_map<Cell, float> gScore;

	// Create a map to store the total cost from start to goal through each node
	std::unordered_map<Cell, float> fScore;

	// Create a map to store the previous node in the shortest path
	std::unordered_map<Cell, Cell> cameFrom;

	// Initialize gScore and fScore to infinity
    for (int x = 0; x < map.GetWidth(); x++) {
        for (int y = 0; y < map.GetHeight(); y++) {
			Cell cell(x, y);
			gScore[cell] = std::numeric_limits<float>::infinity();
			fScore[cell] = std::numeric_limits<float>::infinity();
		}
	}

	// Set the gScore for the start node to 0 and fScore to the heuristic value
	gScore[start] = 0;
	fScore[start] = heuristic(start, goal);

	// Add the start node to the open set
	openSet.insert(start);

	// While the open set is not empty
    while (!openSet.empty()) {
		// Find the node in openSet with the lowest fScore value
		Cell currentNode = *openSet.begin();
        for (const Cell& cell : openSet) {
            if (fScore[cell] < fScore[currentNode]) {
				currentNode = cell;
			}
		}

		// If the current node is the goal, reconstruct the path and return it
        if (currentNode == goal) {
            while (cameFrom.find(currentNode) != cameFrom.end()) {
				shortestPath.push_back(currentNode);
				currentNode = cameFrom[currentNode];
			}
			std::reverse(shortestPath.begin(), shortestPath.end());
			return shortestPath;
		}

		// Remove the current node from the open set and add it to the closed set
		openSet.erase(currentNode);
		closedSet.insert(currentNode);

        // Get the neighbors of the current node
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                // Skip the current node
                if (dx == 0 && dy == 0) {
					continue;
				}

				// Skip diagonal movement if not allowed
                if (!allowDiagonal && dx != 0 && dy != 0) {
					continue;
				}

				// Calculate the neighbor's coordinates
				int x = currentNode.x + dx;
				int y = currentNode.y + dy;

				// Skip out of bounds neighbors
                if (x < 0 || x >= map.GetWidth() || y < 0 || y >= map.GetHeight()) {
					continue;
				}

				// Skip obstacles
                if (map.isObstacle(x, y)) {
					continue;
				}

				// Create the neighbor cell
				Cell neighbor(x, y);

				// Skip neighbors in the closed set
                if (closedSet.find(neighbor) != closedSet.end()) {
					continue;
				}

				// Calculate the tentative gScore
				float tentativeGScore = gScore[currentNode] + heuristic(currentNode, neighbor);

				// If the tentative gScore is less than the gScore for the neighbor
                if (tentativeGScore < gScore[neighbor]) {
					// This path is the best so far, record it
					cameFrom[neighbor] = currentNode;
					gScore[neighbor] = tentativeGScore;
					fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, goal);

					// If the neighbor is not in openSet, add it
                    if (openSet.find(neighbor) == openSet.end()) {
						openSet.insert(neighbor);
					}
				}
            }
        }
    }

    // If the goal was not reached, return an empty path
    return shortestPath;
}