#include "ofApp.h"

#include <Engine/CZPhysics/CZPhysics.h>

#include "Player.h"
#include "Boid.h"

//--------------------------------------------------------------
void ofApp::setup(){
	lastTime = ofGetElapsedTimef();

	FlockingDemo();
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

	// Show the demonstration name
	ofDrawBitmapString("1 - Seek: Seek where the mouse clicks", 10, 20);
	ofDrawBitmapString("2 - Arrive: Arrive where the mouse clicks", 10, 40);
	ofDrawBitmapString("3 - Flee: Seek where the mouse clicks", 10, 60);
	ofDrawBitmapString("4 - Pursue: Pursue the blue player controled by [W][A][S][D]", 10, 80);
	ofDrawBitmapString("5 - Evade: Evade the blue player controled by [W][A][S][D]", 10, 100);
	ofDrawBitmapString("6 - Wander: Wander around leaving a trace", 10, 120);
	ofDrawBitmapString("7 - Flocking: Flocking with the red leader", 10, 140);
	ofDrawBitmapString("Press the number to change the demonstration", 10, 160);
	ofDrawBitmapString("The little white dot represents the target of a boid", 10, 180);

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
			FleeDemo();
			break;
		case '4':
			ClearGameObjects();
			PursueDemo();
			break;
		case '5':
			ClearGameObjects();
			EvadeDemo();
			break;
		case '6':
			ClearGameObjects();
			WanderDemo();
			break;
		case '7':
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

void ofApp::FlockingDemo()
{
	// Create a leader boid
	gameObjects.push_back(new Boid(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(0, 6.28), eBoidState::WANDER, ofColor::red));

	// Create some boids in random positions for flocking
	for (int i = 0; i < 10; i++) {
		gameObjects.push_back(new Boid(&gameObjects));
	}
}