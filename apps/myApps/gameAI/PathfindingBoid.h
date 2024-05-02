#pragma once

#include "Boid.h"

#include "TileMap.h"

class PathfindingBoid : public Boid
{
public:
	PathfindingBoid(TileMap* map, const int i_xCoordinate, const int i_yCoordinate, const float i_orientation, const ofColor i_color = ofColor::white);

	void Update(const float i_deltaTime) override;

	void Draw() override;

	// Input functions
	void mousePressed(int x, int y, int button) override;
	void mouseDragged(int x, int y, int button) override;

private:
	TileMap* map;
	Cell pathfindingTarget;
	std::vector<Cell> path;

	const float maxSpeed = 50.0f;

};

