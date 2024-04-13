#pragma once

#ifndef GAMEAI_PLAYER_H_
#define GAMEAI_PLAYER_H_

#include "GameAIGameObject.h"

struct PlayerInput
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

class Player : public GameAIGameObject
{
public:
	Player();

	void Update(const float i_deltaTime) override;

	void Draw() override;

	void keyPressed(int key) override;

	void keyReleased(int key) override;

private:
	float speed = 500.0f;
	PlayerInput input;
};

#endif // GAMEAI_PLAYER_H_