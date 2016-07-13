#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "ComponentCreator.h"

class ComponentFactory
{
public:
	static ComponentPtr									Create(const std::string& classname);
	static std::map<std::string, ComponentCreator*>&	GetTable();
	static void											Register(const std::string& classname, ComponentCreator* creator);
	static bool											IsClassDerivedFromComponent(const std::string& classname);
};