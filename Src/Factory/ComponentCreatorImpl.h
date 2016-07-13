#pragma once
#include "ComponentCreator.h"

template <class T>
class ComponentCreatorImpl : public ComponentCreator
{
public:
	ComponentCreatorImpl(const std::string& classname) : ComponentCreator(classname) {}

	virtual ComponentPtr Create()
	{
		std::unique_ptr<T> compPtr = std::make_unique<T>();
		return std::move(compPtr);
	}
};