#include "ofApp.h"

#include <Engine/CZPhysics/CZPhysics.h>

#include "Player.h"
#include "Boid.h"

//--------------------------------------------------------------
void ofApp::setup(){
	lastTime = ofGetElapsedTimef();

	//// Make player the first game object
	//gameObjects.push_back(new Player());

	// Create a leader boid
	gameObjects.push_back(new Boid(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(0, 6.28), ofColor::red));

	// Create some boids
	//gameObjects.push_back(new Boid(400.0f, 400.0f, 0.0f, dynamic_cast<Player*>(gameObjects[0])));

	// Create some boids in random positions for flocking
	for (int i = 0; i < 10; i++) {
		gameObjects.push_back(new Boid(&gameObjects));
	}
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->keyPressed(key);
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
