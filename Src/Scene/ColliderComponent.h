#pragma once
#include "stdincl.h"
#include "Shape.h"
#include "Component.h"

class ColliderComponent : public Component
{
	REGISTER(ColliderComponent);

public:

	ColliderComponent(void);
	~ColliderComponent(void);

	virtual void					Update(float dtime) override;
	virtual void					PostUpdate(float dtime) override;

	ObjectRef						GetCollidedObj();
	bool							IsPhantom();

	void							InitShape(const char* shape, const char* csize);
	void							SetIsStatic(bool value);
	void							SetIsPhantom(bool value);

	void							SetCollidedObject(ObjectRef value);

private:

	ObjectRef						m_collidedObject;

	void							CheckObjectForCollider(ObjectRef object);
	void							CheckCollision(ObjectRef object);

	


	void							ParseAttribute(const TiXmlAttribute* attribute) override;

	Shape*							m_shape;

	bool							m_isStatic;
	bool							m_isPhantom;
};

