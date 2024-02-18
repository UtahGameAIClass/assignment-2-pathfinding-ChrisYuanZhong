#pragma once

#ifndef GAMEAI_GAMEAIGAMEOBJECT_H_
#define GAMEAI_GAMEAIGAMEOBJECT_H_

#include <Engine/Assets/GameObject.h>

class GameAIGameObject : public eae6320::Assets::GameObject
{
public:
	GameAIGameObject();

	void Update(float i_deltaTime) override;
	virtual void Draw();
};

#endif  // GAMEAI_GAMEAIGAMEOBJECT_H_
