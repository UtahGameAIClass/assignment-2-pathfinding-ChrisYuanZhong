#pragma once

#include "ofMain.h"

#include "GameAIGameObject.h"
#include "DirectedWeightedGraph.h"
#include "TileMap.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		// AI Behavior Demonstrations
		void ClearGameObjects();
		void SeekDemo();
		void ArriveDemo();
		void AdvancedArriveDemo();
		void FleeDemo();
		void PursueDemo();
		void EvadeDemo();
		void WanderDemo();
		void Wander2Demo();
		void FlockingDemo();

		// Pathfinding Demonstrations
		//void DijkstraDemo();
		void AStarDemo();

		DirectedWeightedGraph CreateSmallGraph();
		DirectedWeightedGraph CreateLargeGraph();

private:
	float lastTime;

	std::vector<GameAIGameObject*> gameObjects;

	DirectedWeightedGraph cityMap;
	std::vector<DirectedWeightedEdge> path;

	float DijkstraTime;
	float AStarTime;

	TileMap* tileMap;
	//std::vector<Cell> mapPath;
};
