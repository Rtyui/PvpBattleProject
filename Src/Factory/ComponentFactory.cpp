#include "ComponentFactory.h"

std::map<std::string, ComponentCreator*>& ComponentFactory::GetTable()
{
	static std::map<std::string, ComponentCreator*> table;
	return table;
}

ComponentPtr ComponentFactory::Create(const std::string& classname)
{
	std::map<std::string, ComponentCreator*>::iterator i;
	i = GetTable().find(classname);

	if (i != GetTable().end())
		return i->second->Create();
	else
		return nullptr;
}

void ComponentFactory::Register(const std::string& classname, ComponentCreator* creator)
{
	GetTable()[classname] = creator;
}

bool ComponentFactory::IsClassDerivedFromComponent(const std::string& classname)
{
	std::map<std::string, ComponentCreator*>::iterator i;
	i = GetTable().find(classname);

	if (i != GetTable().end())
		return true;
	else
		return false;
}