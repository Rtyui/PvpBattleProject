#pragma once
#include "stdincl.h"

class Physics
{
public:
	Physics();
	~Physics();

	static float			GetGravity();

private:

	static float			m_gravity;
};
