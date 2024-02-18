#include "Boid.h"

#include <ofMain.h>

#include <Engine/CZPhysics/SphereCollider.h>

Boid::Boid()
{
	this->SetPosition(eae6320::Math::sVector(100.0f, 100.0f, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(0.0f, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetRotationLocked(true, true, false);
}

Boid::Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, const ofColor i_color) : color(i_color)
{
	this->SetPosition(eae6320::Math::sVector(i_xPosition, i_yPosition, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(i_orientation, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetRotationLocked(true, true, false);

	m_rigidBody->SetAngularVelocity(eae6320::Math::sVector(0.0f, 0.0f, 1.0f));
}

void Boid::Update(const float i_deltaTime)
{
}

void Boid::Draw()
{
	eae6320::Math::sVector position = this->GetPosition();
	
	ofSetColor(color);

	// Draw the circle
	ofDrawCircle(position.x, position.y, 10);

	// Draw the triangle using the orientation
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZRad(-this->GetOrientation().GetZRotation());	// Negative Z rotation because of the coordinate system
	ofDrawTriangle(0, -10, 0, 10, 20, 0);
	ofPopMatrix();
}