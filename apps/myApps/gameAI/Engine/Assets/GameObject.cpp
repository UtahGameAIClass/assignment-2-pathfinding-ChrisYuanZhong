#include "GameObject.h"

eae6320::Assets::GameObject::GameObject()
{
	m_isValid = true;
	m_transform = new Transform();
	m_rigidBody = nullptr;
	m_collider = nullptr;
}

eae6320::Assets::GameObject::~GameObject()
{
	if (m_transform)
		delete m_transform;
	if (m_rigidBody)
		delete m_rigidBody;
	if (m_collider)
		delete m_collider;
}