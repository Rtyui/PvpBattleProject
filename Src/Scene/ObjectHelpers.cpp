#include "ObjectHelpers.h"

ObjectPtr CreateObject()
{
	auto objectPtr = std::make_unique<Object>();
	return std::move(objectPtr);
}