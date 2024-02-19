#pragma once

#ifndef GAMEAI_BOID_H_
#define GAMEAI_BOID_H_

#include <ofColor.h>

#include "GameAIGameObject.h"
#include "Player.h"

class Boid : public GameAIGameObject
{
public:
	Boid();
	Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, Player* i_player, const ofColor i_color = ofColor::white);

	void Update(const float i_deltaTime) override;

	void Draw() override;

	void WrapAround();

	// Input functions
	void mousePressed(int x, int y, int button) override;
	void mouseDragged(int x, int y, int button) override;

	// AI functions
	void LookAt(const eae6320::Math::sVector i_direction);
	eae6320::Math::sVector Seek(const eae6320::Math::sVector i_target);
	eae6320::Math::sVector Arrive(const eae6320::Math::sVector i_target);
	eae6320::Math::sVector Flee(const eae6320::Math::sVector i_target);
	eae6320::Math::sVector Pursue(GameAIGameObject* i_target);
	eae6320::Math::sVector Evade(GameAIGameObject* i_target);
	eae6320::Math::sVector Wander();

private:
	// Color of the boid
	ofColor color = ofColor::white;

	std::vector<eae6320::Math::sVector> trace;

	// AI variables
	const float maxSpeed = 200.0f;
	const float maxForce = 300.0f;

	const float evadeRadius = 2000.0f;
	
	// Arrive parameters
	const float slowRadius = 100.0f;

	// Wander parameters
	const float wanderRadius = 100.0f; // Radius for the wander circle
	const float wanderDistance = 30.0f; // Distance for the wander circle
	const float wanderJitter = 0.5f; // Randomness to be added
	float wanderAngle = 0.0f;

	eae6320::Math::sVector target = eae6320::Math::sVector(0.0f, 0.0f, 0.0f);
	Player* player = nullptr;
};

#endif // GAMEAI_BOID_H_