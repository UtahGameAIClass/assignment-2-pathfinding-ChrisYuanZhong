#include "ofApp.h"

#include <Engine/CZPhysics/CZPhysics.h>

#include "Player.h"
#include "Boid.h"

//--------------------------------------------------------------
void ofApp::setup(){
	lastTime = ofGetElapsedTimef();

	// Make player the first game object
	gameObjects.push_back(new Player());

	// Create some boids
	gameObjects.push_back(new Boid(100.0f, 100.0f, 0.0f));
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
	if (Player* player = dynamic_cast<Player*>(gameObjects[0])) {
		player->keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
if (Player* player = dynamic_cast<Player*>(gameObjects[0])) {
		player->keyReleased(key);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
