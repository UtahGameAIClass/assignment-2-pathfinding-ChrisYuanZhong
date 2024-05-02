#include "ofApp.h"

#include <Engine/CZPhysics/CZPhysics.h>

#include "Player.h"
#include "Boid.h"
#include "PathfindingBoid.h"

#include "Dijkstra.h"
#include "AStar.h"

//--------------------------------------------------------------
void ofApp::setup(){
	lastTime = ofGetElapsedTimef();

	AStarDemo();

	// Create a DirectedWeightedGraph object
	//cityMap = CreateSmallGraph();
	//cityMap = CreateLargeGraph();

	//path = Dijkstra(cityMap, 3, 50);
	//path = AStar(cityMap, 3, 50);

	//AStarTime = ofGetElapsedTimef();
	//path = AStar(cityMap, 3, 50);
	//AStarTime = ofGetElapsedTimef() - AStarTime;

	//DijkstraTime = ofGetElapsedTimef();
	//path = Dijkstra(cityMap, 3, 50);
	//DijkstraTime = ofGetElapsedTimef() - DijkstraTime;
}

//--------------------------------------------------------------
void ofApp::update(){
	// Calculate delta time
	float currentTime = ofGetElapsedTimef();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	ChrisZ::Physics::Update(deltaTime);

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Update(deltaTime);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//// Print the path
	//string pathString = "Path: ";

	//if (path.size() == 0)
	//{
	//	pathString += "No path found";
	//}
	//else
	//{
	//	for each (DirectedWeightedEdge edge in path)
	//	{
	//		pathString += to_string(edge.source) + " -> ";
	//	}
	//	pathString += to_string(path[path.size() - 1].destination);
	//}
	//ofDrawBitmapString(pathString, 10, 20);

	//// Print the time taken by Dijkstra's algorithm
	//ofDrawBitmapString("Dijkstra Time: " + to_string(DijkstraTime), 10, 40);

	//// Print the time taken by A* algorithm
	//ofDrawBitmapString("A* Time: " + to_string(AStarTime), 10, 60);

	// Show the demonstration name
	//ofDrawBitmapString("1 - Seek: Seek where the mouse clicks", 10, 20);
	//ofDrawBitmapString("2 - Arrive: Arrive where the mouse clicks", 10, 40);
	//ofDrawBitmapString("3 - AdvancedArrive: Arrive better where the mouse clicks", 10, 60);
	//ofDrawBitmapString("4 - Flee: Flee from where the mouse clicks", 10, 80);
	//ofDrawBitmapString("5 - Pursue: Pursue the blue player controled by [W][A][S][D]", 10, 100);
	//ofDrawBitmapString("6 - Evade: Evade the blue player controled by [W][A][S][D]", 10, 120);
	//ofDrawBitmapString("7 - Wander: Wander around leaving a trace (Designed by Craig)", 10, 140);
	//ofDrawBitmapString("8 - Wander2: Wander to a random target (Designed by me)", 10, 160);
	//ofDrawBitmapString("9 - Flocking: Flocking with the red leader", 10, 180);
	//ofDrawBitmapString("Press the number to change the demonstration", 10, 200);
	//ofDrawBitmapString("The little white dot represents the target of a boid", 10, 220);


	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Draw();
	}

	ofDrawBitmapString("A* Pathfinding", 10, 20);
	ofDrawBitmapString("Click on the map to set the target", 10, 40);
	ofDrawBitmapString("Red circles represent the path", 10, 60);
	ofDrawBitmapString("Blue circle represents the pathfinding target", 10, 80);
	ofDrawBitmapString("White circle represents the boid's SEEK target", 10, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->keyPressed(key);
	}

	//switch (key) {
	//	case '1':
	//		ClearGameObjects();
	//		SeekDemo();
	//		break;
	//	case '2':
	//		ClearGameObjects();
	//		ArriveDemo();
	//		break;
	//	case '3':
	//		ClearGameObjects();
	//		AdvancedArriveDemo();
	//		break;
	//	case '4':
	//		ClearGameObjects();
	//		FleeDemo();
	//		break;
	//	case '5':
	//		ClearGameObjects();
	//		PursueDemo();
	//		break;
	//	case '6':
	//		ClearGameObjects();
	//		EvadeDemo();
	//		break;
	//	case '7':
	//		ClearGameObjects();
	//		WanderDemo();
	//		break;
	//	case '8':
	//		ClearGameObjects();
	//		Wander2Demo();
	//		break;
	//	case '9':
	//		ClearGameObjects();
	//		FlockingDemo();
	//		break;
	//	case '0':
	//		ClearGameObjects();
	//		AStarDemo();
	//		break;
	//	default:
	//		break;
	//}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->keyReleased(key);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->mouseMoved(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->mouseDragged(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->mousePressed(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->mouseReleased(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->mouseEntered(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->mouseExited(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::ClearGameObjects()
{
	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}
	gameObjects.clear();
}

void ofApp::SeekDemo()
{
	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::SEEK);

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::ArriveDemo()
{
	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::ARRIVE);

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::AdvancedArriveDemo()
{
	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::ADVANCED_ARRIVE);

	// Add the boid to the game objects
	gameObjects.push_back(boid);

}

void ofApp::FleeDemo()
{
	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::FLEE);

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::PursueDemo()
{
	// Make player the first game object
	gameObjects.push_back(new Player());

	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::PURSUE, dynamic_cast<Player*>(gameObjects[0]));

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::EvadeDemo()
{
	// Make player the first game object
	gameObjects.push_back(new Player());

	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::EVADE, dynamic_cast<Player*>(gameObjects[0]));

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::WanderDemo()
{
	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::WANDER);

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::Wander2Demo()
{
	// Create a boid
	Boid* boid = new Boid(400.0f, 400.0f, 0.0f, eBoidState::WANDER2);

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

void ofApp::FlockingDemo()
{
	// Create a leader boid
	gameObjects.push_back(new Boid(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(0, 6.28), eBoidState::WANDER, ofColor::red));

	// Create some boids in random positions for flocking
	for (int i = 0; i < 10; i++) {
		gameObjects.push_back(new Boid(&gameObjects));
	}
}

void ofApp::AStarDemo()
{
	tileMap = new TileMap(100, 75);

	tileMap->SetObstacle(30, 40, true);
	tileMap->SetObstacle(30, 41, true);
	tileMap->SetObstacle(30, 42, true);
	tileMap->SetObstacle(30, 43, true);
	tileMap->SetObstacle(30, 44, true);
	tileMap->SetObstacle(30, 45, true);
	tileMap->SetObstacle(30, 46, true);
	tileMap->SetObstacle(30, 47, true);
	tileMap->SetObstacle(30, 48, true);
	tileMap->SetObstacle(30, 49, true);
	tileMap->SetObstacle(30, 50, true);
	tileMap->SetObstacle(30, 51, true);
	tileMap->SetObstacle(30, 52, true);
	tileMap->SetObstacle(30, 53, true);
	tileMap->SetObstacle(30, 54, true);
	tileMap->SetObstacle(30, 55, true);
	tileMap->SetObstacle(30, 56, true);
	tileMap->SetObstacle(30, 57, true);
	tileMap->SetObstacle(30, 58, true);
	tileMap->SetObstacle(30, 59, true);
	tileMap->SetObstacle(30, 60, true);

	tileMap->SetObstacle(50, 50, true);
	tileMap->SetObstacle(50, 51, true);
	tileMap->SetObstacle(50, 52, true);
	tileMap->SetObstacle(50, 53, true);
	tileMap->SetObstacle(50, 54, true);
	tileMap->SetObstacle(50, 55, true);
	tileMap->SetObstacle(50, 56, true);
	tileMap->SetObstacle(50, 57, true);
	tileMap->SetObstacle(50, 58, true);
	tileMap->SetObstacle(50, 59, true);
	tileMap->SetObstacle(50, 60, true);
	tileMap->SetObstacle(50, 61, true);
	tileMap->SetObstacle(50, 62, true);
	tileMap->SetObstacle(50, 63, true);
	tileMap->SetObstacle(50, 64, true);
	tileMap->SetObstacle(50, 65, true);
	tileMap->SetObstacle(50, 66, true);
	tileMap->SetObstacle(50, 67, true);
	tileMap->SetObstacle(50, 68, true);
	tileMap->SetObstacle(50, 69, true);
	tileMap->SetObstacle(50, 70, true);

	tileMap->SetObstacle(40, 15, true);
	tileMap->SetObstacle(40, 16, true);
	tileMap->SetObstacle(40, 17, true);
	tileMap->SetObstacle(40, 18, true);
	tileMap->SetObstacle(40, 19, true);
	tileMap->SetObstacle(40, 20, true);
	tileMap->SetObstacle(40, 21, true);
	tileMap->SetObstacle(40, 22, true);
	tileMap->SetObstacle(40, 23, true);
	tileMap->SetObstacle(40, 24, true);
	tileMap->SetObstacle(40, 25, true);
	tileMap->SetObstacle(40, 26, true);
	tileMap->SetObstacle(40, 27, true);
	tileMap->SetObstacle(40, 28, true);
	tileMap->SetObstacle(40, 29, true);
	tileMap->SetObstacle(40, 30, true);
	tileMap->SetObstacle(40, 31, true);
	tileMap->SetObstacle(40, 32, true);
	tileMap->SetObstacle(40, 33, true);
	tileMap->SetObstacle(40, 34, true);

	// Create a boid
	PathfindingBoid* boid = new PathfindingBoid(tileMap, 5.0f, 20.0f, 0.0f);

	// Add the boid to the game objects
	gameObjects.push_back(boid);
}

DirectedWeightedGraph ofApp::CreateSmallGraph()
{
	DirectedWeightedGraph smallGraph;

	// Add nodes (cities)
	std::vector<Node> cities = {
		Node(10, 75), Node(45, 20), Node(70, 85), Node(30, 50),
		Node(55, 95), Node(90, 60), Node(20, 35), Node(80, 10)
	};

	for (int i = 0; i < cities.size(); ++i) {
		smallGraph.addNode(i, cities[i]);
	}

	// Use Euclidean distance as edge weight
	smallGraph.addEdge(DirectedWeightedEdge(0, 1, 70.71f));
	smallGraph.addEdge(DirectedWeightedEdge(0, 2, 60.83f));
	smallGraph.addEdge(DirectedWeightedEdge(0, 3, 32.02f));
	smallGraph.addEdge(DirectedWeightedEdge(1, 2, 67.18f));
	smallGraph.addEdge(DirectedWeightedEdge(1, 3, 36.06f));
	smallGraph.addEdge(DirectedWeightedEdge(1, 4, 75.33f));
	smallGraph.addEdge(DirectedWeightedEdge(2, 4, 17.49f));
	smallGraph.addEdge(DirectedWeightedEdge(2, 5, 29.68f));
	smallGraph.addEdge(DirectedWeightedEdge(3, 6, 15.13f));
	smallGraph.addEdge(DirectedWeightedEdge(4, 5, 47.17f));
	smallGraph.addEdge(DirectedWeightedEdge(4, 7, 87.80f));
	smallGraph.addEdge(DirectedWeightedEdge(5, 7, 50.00f));
	smallGraph.addEdge(DirectedWeightedEdge(6, 7, 66.94f));
	smallGraph.addEdge(DirectedWeightedEdge(7, 1, 37.42f));


	return smallGraph;
}

DirectedWeightedGraph ofApp::CreateLargeGraph()
{
	DirectedWeightedGraph largeGraph;

	// Number of edges
	int numEdges = 10000;

	// Start with a certain number of nodes (e.g., square root of number of edges)
	int numNodes = static_cast<int>(sqrt(numEdges));

	// Add nodes
	for (int i = 0; i < numNodes; ++i) {
		float x = static_cast<float>(rand() % 1000);  // Random x coordinate between 0 and 1000
		float y = static_cast<float>(rand() % 1000);  // Random y coordinate between 0 and 1000
		largeGraph.addNode(i, Node(x, y));
	}

	// Add edges
	for (int i = 0; i < numEdges; ++i) {
		int source = rand() % numNodes;  // Random source node
		int destination = rand() % numNodes;  // Random destination node
		while (source == destination) {  // Ensure source and destination are not the same
			destination = rand() % numNodes;
		}
		// Calculate Euclidean distance between source and destination nodes
		float dx = largeGraph.getNode(source).x - largeGraph.getNode(destination).x;
		float dy = largeGraph.getNode(source).y - largeGraph.getNode(destination).y;
		float weight = sqrt(dx * dx + dy * dy);  // Euclidean distance
		largeGraph.addEdge(DirectedWeightedEdge(source, destination, weight));
	}

	return largeGraph;
}