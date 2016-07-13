#pragma once
#include "stdincl.h"
#include "ComponentCreatorImpl.h"

class Object;

typedef std::unique_ptr<Object> ObjectPtr;
typedef Object* ObjectRef;

#define REGISTER(classname) \
private: \
   static const ComponentCreatorImpl<classname> creator;

#define REGISTERIMPL(classname) \
   const ComponentCreatorImpl<classname> classname::creator(#classname);

class Component
{
	REGISTER(Component);
public:
	Component();
	~Component();

	virtual void		Update(float dtime);
	virtual void		PostUpdate(float dtime);

	virtual void		Draw();

	virtual void		ParseAttributes(const TiXmlElement* element);

	virtual void		OnAddToObject();

	virtual void		OnStart();
	virtual void		OnActivate();

	ObjectRef			m_object;
protected:

	virtual void		ParseAttribute(const TiXmlAttribute* attribute);
};