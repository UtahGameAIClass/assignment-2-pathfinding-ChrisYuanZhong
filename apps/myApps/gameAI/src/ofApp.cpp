#include "ofApp.h"

#include <Engine/CZPhysics/CZPhysics.h>

#include "Player.h"
#include "Boid.h"

#include "Dijkstra.h"
#include "AStar.h"

//--------------------------------------------------------------
void ofApp::setup(){
	lastTime = ofGetElapsedTimef();

	//FlockingDemo();

	// Create a DirectedWeightedGraph object
	cityMap = CreateCityMap();
	path = AStar(cityMap, 0, 14);
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
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Draw();
	}

	// Print the path
	string pathString = "Path: ";
	for each (DirectedWeightedEdge edge in path)
	{
		pathString += to_string(edge.source) + " -> ";
	}
	pathString += to_string(path[path.size() - 1].destination);
	ofDrawBitmapString(pathString, 10, 20);

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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->keyPressed(key);
	}

	switch (key) {
		case '1':
			ClearGameObjects();
			SeekDemo();
			break;
		case '2':
			ClearGameObjects();
			ArriveDemo();
			break;
		case '3':
			ClearGameObjects();
			AdvancedArriveDemo();
			break;
		case '4':
			ClearGameObjects();
			FleeDemo();
			break;
		case '5':
			ClearGameObjects();
			PursueDemo();
			break;
		case '6':
			ClearGameObjects();
			EvadeDemo();
			break;
		case '7':
			ClearGameObjects();
			WanderDemo();
			break;
		case '8':
			ClearGameObjects();
			Wander2Demo();
			break;
		case '9':
			ClearGameObjects();
			FlockingDemo();
			break;
		default:
			break;
	}
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

DirectedWeightedGraph ofApp::CreateCityMap()
{
	// Create a DirectedWeightedGraph object
	DirectedWeightedGraph cityMap;

	// Add edges to the graph representing roads between intersections
	cityMap.addEdge(DirectedWeightedEdge(0, 1, 3));
	cityMap.addEdge(DirectedWeightedEdge(0, 2, 4));
	cityMap.addEdge(DirectedWeightedEdge(1, 3, 2));
	cityMap.addEdge(DirectedWeightedEdge(1, 4, 5));
	cityMap.addEdge(DirectedWeightedEdge(2, 5, 6));
	cityMap.addEdge(DirectedWeightedEdge(3, 6, 3));
	cityMap.addEdge(DirectedWeightedEdge(4, 6, 4));
	cityMap.addEdge(DirectedWeightedEdge(4, 7, 2));
	cityMap.addEdge(DirectedWeightedEdge(5, 7, 5));
	cityMap.addEdge(DirectedWeightedEdge(6, 8, 6));
	cityMap.addEdge(DirectedWeightedEdge(7, 8, 3));
	cityMap.addEdge(DirectedWeightedEdge(7, 9, 4));
	cityMap.addEdge(DirectedWeightedEdge(8, 9, 2));
	cityMap.addEdge(DirectedWeightedEdge(9, 10, 5));
	cityMap.addEdge(DirectedWeightedEdge(10, 11, 6));
	cityMap.addEdge(DirectedWeightedEdge(11, 12, 3));
	cityMap.addEdge(DirectedWeightedEdge(12, 13, 4));
	cityMap.addEdge(DirectedWeightedEdge(13, 14, 2));
	cityMap.addEdge(DirectedWeightedEdge(14, 0, 5));

	return cityMap;
}

DirectedWeightedGraph ofApp::CreateLargeGraph()
{
	// Number of vertices in the graph
	const int numVertices = 10000; // Adjust this number as needed

	// Create a DirectedWeightedGraph object
	DirectedWeightedGraph largeGraph;

	// Seed the random number generator
	srand(time(nullptr));

	// Generate random edges with positive integer weights
	for (int i = 0; i < numVertices; ++i) {
		// Randomly decide how many edges to create for each vertex
		int numEdges = rand() % 10 + 1; // Each vertex will have 1 to 10 edges

		for (int j = 0; j < numEdges; ++j) {
			int destination = rand() % numVertices;
			int weight = rand() % 100 + 1; // Weight between 1 and 100

			// Add the edge to the graph
			largeGraph.addEdge(DirectedWeightedEdge(i, destination, weight));
		}
	}

	return largeGraph;
}