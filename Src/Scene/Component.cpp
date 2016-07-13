#include "Component.h"
#include "Helpers.h"

REGISTERIMPL(Component);

Component::Component()
{
}

Component::~Component()
{
}

void Component::Update(float dtime)
{
}

void Component::PostUpdate(float dtime)
{
}

void Component::Draw()
{
}

void Component::ParseAttributes(const TiXmlElement* element)
{
	for (auto a = element->FirstAttribute(); a; a = a->Next())
	{
		ParseAttribute(a);
	}
}

void Component::OnAddToObject()
{
}

void Component::OnStart()
{
}

void Component::OnActivate()
{
}

void Component::ParseAttribute(const TiXmlAttribute* attribute)
{
	
}
