#include "Boid.h"

#include <ofMain.h>

Boid::Boid()
{
	this->SetPosition(eae6320::Math::sVector(100.0f, 100.0f, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(0.0f, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));
}

Boid::Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, const ofColor i_color) : color(i_color)
{
	this->SetPosition(eae6320::Math::sVector(i_xPosition, i_yPosition, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(i_orientation, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));
}

void Boid::Draw()
{
	eae6320::Math::sVector position = this->GetPosition();
	eae6320::Math::cQuaternion orientation = this->GetOrientation();

	// Draw the boid
	// The circle represents the body of the boid
	// The triangle represents the direction of the boid
	ofDrawCircle(position.x, position.y, 10);
	//ofDrawTriangle(position.x, position.y - 10, position.x, position.y + 10, position.x + 20, position.y);

	// Draw the boid using the orientation
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZRad(-orientation.GetZRotation());
	ofSetColor(color);
	ofDrawTriangle(0, -10, 0, 10, 20, 0);
	ofPopMatrix();
}

// Helper function