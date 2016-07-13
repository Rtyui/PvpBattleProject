#include "Physics.h"

float Physics::m_gravity = 12.f;

Physics::Physics()
{
}

Physics::~Physics()
{
}

float Physics::GetGravity()
{
	return m_gravity;
}