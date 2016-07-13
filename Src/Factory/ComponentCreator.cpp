#include "ComponentCreator.h"
#include "ComponentFactory.h"

ComponentCreator::ComponentCreator(const std::string& classname)
{
	ComponentFactory::Register(classname, this);
}