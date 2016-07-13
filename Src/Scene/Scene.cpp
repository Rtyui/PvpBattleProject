#include "Scene.h"
#include "ObjectHelpers.h"

Scene* g_scene;

Scene::Scene()
{
	GetRoot()->SetName("root");
	g_scene = this;
}

Scene::~Scene()
{
}

void Scene::Update(float dtime)
{
	GetRoot()->Update(dtime);
}

void Scene::PostUpdate(float dtime)
{
	GetRoot()->PostUpdate(dtime);
}

ObjectRef Scene::GetRoot()
{
	static ObjectPtr root = std::move(CreateObject());
	return root.get();
}