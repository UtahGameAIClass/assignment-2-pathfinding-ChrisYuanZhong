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

	// Input functions
	void mouseDragged(int x, int y, int button) override;

	// AI functions
	eae6320::Math::sVector Seek(const eae6320::Math::sVector i_target);
	eae6320::Math::sVector Flee(const eae6320::Math::sVector i_target);
	eae6320::Math::sVector Pursue(GameAIGameObject* i_target);

private:
	// Color of the boid
	ofColor color = ofColor::white;

	// AI variables
	const float maxSpeed = 300.0f;
	const float maxForce = 150.0f;

	eae6320::Math::sVector target = eae6320::Math::sVector(0.0f, 0.0f, 0.0f);
	Player* player = nullptr;
};

#endif // GAMEAI_BOID_H_