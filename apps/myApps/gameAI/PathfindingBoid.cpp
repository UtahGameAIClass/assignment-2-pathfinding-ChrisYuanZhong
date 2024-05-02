#include "PathfindingBoid.h"

#include <Engine/CZPhysics/SphereCollider.h>
#include "AStar.h"


PathfindingBoid::PathfindingBoid(TileMap* map, const int i_xCoordinate, const int i_yCoordinate, const float i_orientation, const ofColor i_color)
{
	this->map = map;

	this->SetPosition(eae6320::Math::sVector(map->GetxPosition(i_xCoordinate), map->GetyPosition(i_yCoordinate), 0.0f));
	this->SetOrientation(eae6320::Math::cQuaternion(i_orientation, eae6320::Math::sVector(0.0f, 0.0f, 1.0f)));
	this->state = eBoidState::SEEK;
	this->color = i_color;

	m_rigidBody = new ChrisZ::Physics::RigidBody(this);
	m_collider = new ChrisZ::Physics::SphereCollider(eae6320::Math::sVector(0.0f, 0.0f, 0.0f), 10.0f, this);

	m_rigidBody->SetDragCoefficient(0.5f);
	m_rigidBody->SetRotationLocked(true, true, false);

	target = this->GetPosition();
}

void PathfindingBoid::Update(const float i_deltaTime)
{
	trace.push_back(this->GetPosition());

	eae6320::Math::sVector velocity = m_rigidBody->GetVelocity();

	// Limit the speed
	if (velocity.GetLength() > maxSpeed)
	{
		velocity = velocity.GetNormalized() * maxSpeed;
	}
	m_rigidBody->SetVelocity(velocity);

	// AI
	LookAt(velocity);

	// Update the target based on the pathfinding path
	if (!path.empty())
	{
		// If the current position is close enough to the current target
		if ((target - this->GetPosition()).GetLength() < map->GetTileSize())
		{
			// Remove the current target from the path
			path.erase(path.begin());

			// If there are still cells left in the path
			if (!path.empty())
			{
				// Update the target with the next cell in the path
				target = eae6320::Math::sVector(map->GetxPosition(path[0].x), map->GetyPosition(path[0].y), 0.0f);
			}
		}
	}

	this->m_rigidBody->AddForce(Seek(target));
}

void PathfindingBoid::Draw()
{
	// Draw the tile map
	for (int y = 0; y < map->GetHeight(); ++y) {
		for (int x = 0; x < map->GetWidth(); ++x) {
			if (map->isObstacle(x, y)) {
				ofSetColor(ofColor::white);
			}
			else {
				ofSetColor(ofColor::black);
			}
			ofDrawRectangle(x * map->GetTileSize(), y * map->GetTileSize(), map->GetTileSize(), map->GetTileSize());
		}
	}

	ofSetColor(ofColor::red);
	// Draw the pathfinding path
	for (int i = 0; i < path.size(); i++)
	{
		ofDrawCircle(map->GetxPosition(path[i].x), map->GetyPosition(path[i].y), 5);
	}

	ofSetColor(ofColor::blue);
	// Draw the pathfinding target
	ofDrawCircle(map->GetxPosition(pathfindingTarget.x), map->GetyPosition(pathfindingTarget.y), 5);


	eae6320::Math::sVector position = this->GetPosition();

	ofSetColor(color);

	// Draw the target
	ofDrawCircle(target.x, target.y, 5);

	// Draw the trace
	for (int i = 0; i < trace.size(); i++)
	{
		ofDrawCircle(trace[i].x, trace[i].y, 1);
	}

	// Draw the circle
	ofDrawCircle(position.x, position.y, 10);

	// Draw the triangle using the orientation
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZRad(-this->GetOrientation().GetZRotation());	// Negative Z rotation because of the coordinate system
	ofDrawTriangle(0, -10, 0, 10, 20, 0);
	ofPopMatrix();
}

void PathfindingBoid::mousePressed(int x, int y, int button)
{
	this->pathfindingTarget = Cell(map->GetxIndex(x), map->GetyIndex(y));
	path = AStar(*map, Cell(map->GetxIndex(this->GetPosition().x), map->GetyIndex(this->GetPosition().y)), pathfindingTarget, true);
	target = eae6320::Math::sVector(map->GetxPosition(path[0].x), map->GetyPosition(path[0].y), 0.0f);
}

void PathfindingBoid::mouseDragged(int x, int y, int button)
{
	this->pathfindingTarget = Cell(map->GetxIndex(x), map->GetyIndex(y));
	path = AStar(*map, Cell(map->GetxIndex(this->GetPosition().x), map->GetyIndex(this->GetPosition().y)), pathfindingTarget, true);
	target = eae6320::Math::sVector(map->GetxPosition(path[0].x), map->GetyPosition(path[0].y), 0.0f);
}