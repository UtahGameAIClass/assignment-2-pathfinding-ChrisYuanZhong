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
	Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, const ofColor i_color = ofColor::white);
	Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, Player* i_player, const ofColor i_color = ofColor::white);
	Boid(std::vector<GameAIGameObject*>* i_boids, const ofColor i_color = ofColor::white);

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

	// Flocking functions
	bool IsLeader() const;
	float GetWeight() const;
	eae6320::Math::sVector Align(std::vector<GameAIGameObject*> i_boids);
	eae6320::Math::sVector Cohesion(std::vector<GameAIGameObject*> i_boids);
	eae6320::Math::sVector Separation(std::vector<GameAIGameObject*> i_boids);
	eae6320::Math::sVector Flock(std::vector<GameAIGameObject*> i_boids);

private:
	// Color of the boid
	ofColor color = ofColor::white;

	std::vector<eae6320::Math::sVector> trace;

	// AI variables
	const float maxSpeed = 150.0f;
	const float maxForce = 300.0f;

	const float evadeRadius = 2000.0f;
	
	// Arrive parameters
	const float slowRadius = 100.0f;

	// Wander parameters
	const float wanderRadius = 100.0f; // Radius for the wander circle
	const float wanderDistance = 30.0f; // Distance for the wander circle
	const float wanderJitter = 0.5f; // Randomness to be added
	float wanderAngle = 0.0f;

	// Flocking parameters
	const float perceptionRadius = 10000.0f;
	const float separationRadius = 40.0f;
	const float alignMultiplier = 0.5f;
	const float cohesionMultiplier = 1.5f;
	const float separationMultiplier = 2.0f;
	const float leaderMultiplier = 10.0f;

	float weight = 1.0f;

	eae6320::Math::sVector target = eae6320::Math::sVector(0.0f, 0.0f, 0.0f);
	Player* player = nullptr;
	std::vector<GameAIGameObject*>* boids = nullptr;
};

#endif // GAMEAI_BOID_H_