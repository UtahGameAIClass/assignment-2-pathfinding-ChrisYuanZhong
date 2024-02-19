#define _USE_MATH_DEFINES

#include "Boid.h"

#include <algorithm>
#include <math.h>
#include <ofMain.h>

#include <Engine/CZPhysics/SphereCollider.h>

Boid::Boid()
{
	this->SetPosition(eae6320::Math::sVector(100.0f, 100.0f, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(0.0f, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetDragCoefficient(0.5f);
	m_rigidBody->SetRotationLocked(true, true, false);

	target = this->GetPosition();
}

Boid::Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, Player* i_player, const ofColor i_color) : color(i_color)
{
	this->SetPosition(eae6320::Math::sVector(i_xPosition, i_yPosition, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(i_orientation, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetDragCoefficient(0.5f);
	m_rigidBody->SetRotationLocked(true, true, false);

	//m_rigidBody->SetAngularVelocity(eae6320::Math::sVector(0.0f, 0.0f, -1.0f));

	target = this->GetPosition();
	player = i_player;
}

void Boid::Update(const float i_deltaTime)
{
	WrapAround();

	eae6320::Math::sVector velocity = m_rigidBody->GetVelocity();

	// Limit the speed
	if (velocity.GetLength() > maxSpeed)
	{
		velocity = velocity.GetNormalized() * maxSpeed;
	}
	m_rigidBody->SetVelocity(velocity);

	// AI
	LookAt(velocity);
	//this->m_rigidBody->AddForce(Arrive(target));
	this->m_rigidBody->AddForce(Evade(player));
}

void Boid::Draw()
{
	eae6320::Math::sVector position = this->GetPosition();
	
	ofSetColor(color);

	// This is for drawing the predicted position
	ofDrawCircle(target.x, target.y, 5);

	// Draw the circle
	ofDrawCircle(position.x, position.y, 10);

	// Draw the triangle using the orientation
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZRad(-this->GetOrientation().GetZRotation());	// Negative Z rotation because of the coordinate system
	ofDrawTriangle(0, -10, 0, 10, 20, 0);
	ofPopMatrix();
}

void Boid::WrapAround()
{
	eae6320::Math::sVector position = this->GetPosition();

	if (position.x < 0)
	{
		position.x = ofGetWidth();
	}
	else if (position.x > ofGetWidth())
	{
		position.x = 0;
	}

	if (position.y < 0)
	{
		position.y = ofGetHeight();
	}
	else if (position.y > ofGetHeight())
	{
		position.y = 0;
	}

	this->SetPosition(position);
}

void Boid::mousePressed(int x, int y, int button)
{
	this->target = eae6320::Math::sVector(x, y, 0.0f);
}

void Boid::mouseDragged(int x, int y, int button)
{
	this->target = eae6320::Math::sVector(x, y, 0.0f);
}

// AI functions

void Boid::LookAt(const eae6320::Math::sVector i_direction)
{
	float angle = atan2(i_direction.y, i_direction.x);
	this->SetOrientation(eae6320::Math::cQuaternion(-angle, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));	// Negative Z rotation because of the coordinate system
}

eae6320::Math::sVector Boid::Seek(const eae6320::Math::sVector i_target)
{
	eae6320::Math::sVector desiredVelocity = i_target - this->GetPosition();

	if (desiredVelocity.GetLength() != 0.0f)
	{
		desiredVelocity = desiredVelocity.GetNormalized() * maxSpeed;
		eae6320::Math::sVector force = desiredVelocity - m_rigidBody->GetVelocity();

		// Limit the force
		if (force.GetLength() > maxForce)
		{
			force = force.GetNormalized() * maxForce;
		}

		return force;
	}
	else
	{
		return eae6320::Math::sVector(0.0f, 0.0f, 0.0f);
	}
}

eae6320::Math::sVector Boid::Arrive(const eae6320::Math::sVector i_target)
{
	eae6320::Math::sVector desiredVelocity = i_target - this->GetPosition();

	if (desiredVelocity.GetLength() != 0.0f)
	{
		float distance = desiredVelocity.GetLength();

		if (distance < slowRadius)
		{
			float desiredVelocityMagnitude = distance * maxSpeed / slowRadius;
			desiredVelocity = desiredVelocity.GetNormalized() * desiredVelocityMagnitude;
		}
		else
		{
			desiredVelocity = desiredVelocity.GetNormalized() * maxSpeed;
		}

		eae6320::Math::sVector force = desiredVelocity - m_rigidBody->GetVelocity();

		// Limit the force
		if (force.GetLength() > maxForce)
		{
			force = force.GetNormalized() * maxForce;
		}

		return force;
	}
	else
	{
		return eae6320::Math::sVector(0.0f, 0.0f, 0.0f);
	}
}

eae6320::Math::sVector Boid::Flee(const eae6320::Math::sVector i_target)
{
	return -Seek(i_target);
}

eae6320::Math::sVector Boid::Pursue(GameAIGameObject* i_target)
{
	eae6320::Math::sVector distance = i_target->GetPosition() - this->GetPosition();
	//float updatesNeeded = distance.GetLength() / maxSpeed;

	float updatesNeeded = 1.0f;
	if (i_target->GetRigidBody()->GetVelocity().GetLength() != 0.0f)
	{
		float updatesNeeded = distance.GetLength() / i_target->GetRigidBody()->GetVelocity().GetLength();
	}

	eae6320::Math::sVector futurePosition = i_target->GetPosition() + i_target->GetRigidBody()->GetVelocity() * updatesNeeded;

	// This is for drawing the predicted position
	target = futurePosition;

	return Seek(futurePosition);
}

eae6320::Math::sVector Boid::Evade(GameAIGameObject* i_target)
{
	eae6320::Math::sVector distance = i_target->GetPosition() - this->GetPosition();

	if (distance.GetLength() > evadeRadius)
	{
		return eae6320::Math::sVector(0.0f, 0.0f, 0.0f);
	}

	return -Pursue(i_target);
}
