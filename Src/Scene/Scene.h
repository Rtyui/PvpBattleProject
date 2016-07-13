#pragma once

#include "Object.h"

class Scene
{
public:
	Scene();
	~Scene();

	void		Update(float dtime);
	void		PostUpdate(float dtime);

	ObjectRef	GetRoot();

private:
};

extern Scene* g_scene;