#pragma once
#include "stdincl.h"
class Component;

typedef std::unique_ptr<Component> ComponentPtr;
typedef Component* ComponentRef;

class ComponentCreator
{
public:
	ComponentCreator(const std::string& classname);

	virtual ComponentPtr Create() = 0;
};
