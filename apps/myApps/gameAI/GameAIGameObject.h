#pragma once

#ifndef GAMEAI_GAMEAIGAMEOBJECT_H_
#define GAMEAI_GAMEAIGAMEOBJECT_H_

#include <ofMain.h>

#include <Engine/Assets/GameObject.h>

class GameAIGameObject : public eae6320::Assets::GameObject
{
public:
	GameAIGameObject();

	void Update(float i_deltaTime) override;
	virtual void Draw();

	// Input functions from openFrameworks
	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mouseDragged(int x, int y, int button);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);
	virtual void mouseEntered(int x, int y);
	virtual void mouseExited(int x, int y);
};

#endif  // GAMEAI_GAMEAIGAMEOBJECT_H_
