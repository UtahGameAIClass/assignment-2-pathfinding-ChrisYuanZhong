#include "Player.h"

#include <ofMain.h>

#include <Engine/CZPhysics/SphereCollider.h>

Player::Player()
{
	this->SetPosition(eae6320::Math::sVector(500.0f, 500.0f, 0.0f));

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);
	m_rigidBody->SetDragCoefficient(2.0f);

	m_rigidBody->SetRotationLocked(true, true, true);
}

void Player::Update(const float i_deltaTime)
{
	// Movement

	if (input.left)
	{
		m_rigidBody->AddForce(eae6320::Math::sVector(-speed, 0.0f, 0.0f));
	}
	if (input.right)
	{
		m_rigidBody->AddForce(eae6320::Math::sVector(speed, 0.0f, 0.0f));
	}
	if (input.up)
	{
		m_rigidBody->AddForce(eae6320::Math::sVector(0.0f, -speed, 0.0f));
	}
	if (input.down)
	{
		m_rigidBody->AddForce(eae6320::Math::sVector(0.0f, speed, 0.0f));
	}
}

void Player::Draw()
{
	eae6320::Math::sVector position = this->GetPosition();

	// Draw the circle
	ofSetColor(ofColor::aqua);
	ofDrawCircle(position.x, position.y, 10);
}

void Player::keyPressed(int key)
{
	if (key == OF_KEY_LEFT || key == 'a')
	{
		input.left = true;
	}
	else if (key == OF_KEY_RIGHT || key == 'd')
	{
		input.right = true;
	}
	else if (key == OF_KEY_UP || key == 'w')
	{
		input.up = true;
	}
	else if (key == OF_KEY_DOWN || key == 's')
	{
		input.down = true;
	}
}

void Player::keyReleased(int key)
{
	if (key == OF_KEY_LEFT || key == 'a')
	{
		input.left = false;
	}
	else if (key == OF_KEY_RIGHT || key == 'd')
	{
		input.right = false;
	}
	else if (key == OF_KEY_UP || key == 'w')
	{
		input.up = false;
	}
	else if (key == OF_KEY_DOWN || key == 's')
	{
		input.down = false;
	}
}

