#pragma once

#ifndef GAMEAI_BOID_H_
#define GAMEAI_BOID_H_

#include <ofColor.h>

#include "GameAIGameObject.h"

class Boid : public GameAIGameObject
{
public:
	Boid();
	Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, const ofColor i_color = ofColor::white);
	//~Boid();

	void Update(const float i_deltaTime) override;

	void Draw() override;

private:
	// Color of the boid
	ofColor color = ofColor::white;
};

#endif // GAMEAI_BOID_H_