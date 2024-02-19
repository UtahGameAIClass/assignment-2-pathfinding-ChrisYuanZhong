#include "Boid.h"

#include <algorithm>
#include <ofMain.h>

#include <Engine/CZPhysics/SphereCollider.h>

Boid::Boid()
{
	this->SetPosition(eae6320::Math::sVector(100.0f, 100.0f, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(0.0f, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetDragCoefficient(0.0f);
	m_rigidBody->SetRotationLocked(true, true, false);

	target = this->GetPosition();
}

Boid::Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, Player* i_player, const ofColor i_color) : color(i_color)
{
	this->SetPosition(eae6320::Math::sVector(i_xPosition, i_yPosition, 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(i_orientation, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetDragCoefficient(0.0f);
	m_rigidBody->SetRotationLocked(true, true, false);

	m_rigidBody->SetAngularVelocity(eae6320::Math::sVector(0.0f, 0.0f, 1.0f));

	target = this->GetPosition();
	player = i_player;
}

void Boid::Update(const float i_deltaTime)
{
	eae6320::Math::sVector velocity = m_rigidBody->GetVelocity();

	// Limit the speed
	if (velocity.GetLength() > maxSpeed)
	{
		velocity = velocity.GetNormalized() * maxSpeed;
	}
	m_rigidBody->SetVelocity(velocity);
	
	//cout << velocity.x << " " << velocity.y << " " << velocity.z << endl;

	// Look where you're going
	if (velocity.GetLength() > 0.0f)
	{
		// Use AddTorque to rotate the boid
		eae6320::Math::sVector forward = velocity.GetNormalized();
		eae6320::Math::sVector right = eae6320::Math::sVector(-forward.y, forward.x, 0.0f);
		float dot = forward.x * right.y - forward.y * right.x;
		float angle = std::acos(forward.x) * (forward.y < 0.0f ? -1.0f : 1.0f);
		m_rigidBody->AddTorque(eae6320::Math::sVector(0.0f, 0.0f, dot * angle));
	}

	// AI
	this->m_rigidBody->AddForce(Pursue(player));
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

void Boid::mouseDragged(int x, int y, int button)
{
	this->target = eae6320::Math::sVector(x, y, 0.0f);
}

// AI functions
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

eae6320::Math::sVector Boid::Flee(const eae6320::Math::sVector i_target)
{
	return -Seek(i_target);
}

eae6320::Math::sVector Boid::Pursue(GameAIGameObject* i_target)
{
	eae6320::Math::sVector distance = i_target->GetPosition() - this->GetPosition();
	float updatesNeeded = distance.GetLength() / maxSpeed;
	eae6320::Math::sVector futurePosition = i_target->GetPosition() + i_target->GetRigidBody()->GetVelocity() * updatesNeeded;

	// This is for drawing the predicted position
	target = futurePosition;

	return Seek(futurePosition);
}
