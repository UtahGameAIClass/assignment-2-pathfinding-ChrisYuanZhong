#pragma once

#ifndef GAMEAI_BOID_H_
#define GAMEAI_BOID_H_

#include <Engine/Assets/GameObject.h>

#include <ofColor.h>

class Boid : public eae6320::Assets::GameObject
{
public:
	Boid();
	Boid(const float i_xPosition, const float i_yPosition, const float i_orientation, const ofColor i_color = ofColor::white);
	//~Boid();

	//void Update();

	void Draw();

private:
	// Color of the boid
	ofColor color = ofColor::white;
};

#endif // GAMEAI_BOID_H_