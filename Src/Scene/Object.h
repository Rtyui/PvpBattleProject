#pragma once

#include "stdincl.h"
#include "Component.h"
#include <SFML/Graphics.hpp>

class Object
{
public:

	Object();
	~Object();

	void					OnStart();
	void					OnActivate();
	void					Update(float dtime);
	void					PostUpdate(float dtime);
	void					Draw();

	static ObjectPtr		CreateFromFile(const std::string& filename);
	static ObjectPtr		CreateFromXML(const TiXmlElement* element);
	static ObjectPtr		Create();

	void					UpdateGTM();

	std::string				GetName();

	Vector2f				GetPos();
	Vector2f				GetGlobalPos();
	Vector2f				GetScale();
	Vector2f				GetOrigin();

	sf::Transform			GetTransform();
	sf::Transformable		GetTransformable();

	float					GetRotation();
	float					GetGlobalRotation();

	ObjectRef				GetParent();

	ObjectRef				GetChild(uint index);
	ObjectRef				FindChild(const std::string& name);

	uint					AddChild(ObjectPtr&& child);
	void					InsertChild(ObjectPtr&& child, uint index);

	void					RemoveChild(uint i);
	void					RemoveChild(const std::string& name);

	uint					GetChildrenCount();

	template <typename T>
    T*						GetComponent()
	{
		for (uint i = 0; i < m_components.size(); ++i)
		{
			m_components[i];
			T* comp = dynamic_cast<T*>(m_components[i].get());
			if (comp) return comp;
		}
		return nullptr;
	}
	template <typename T>
    T*						AddComponent()
	{
		std::unique_ptr<T> compPtr = std::make_unique<T>();
		compPtr->m_object = this;
		T* compRef = compPtr.get();
		m_components.push_back(std::move(compPtr));
		return compRef;
	}
	void					AddComponent(ComponentPtr&& comp);

	void					Enable();
	void					Disable();
	bool					IsEnabled();

	void					SetName(std::string name);
	void					SetEnabled(bool enabled);
	void					SetPos(Vector2f pos);
	void					SetScale(Vector2f scale);
	void					SetOrigin(Vector2f origin);
	void					SetRotation(float rot);
	void					SetParent(Object* parent);
	void					SetDirty();
	void					SetJustEnabled();

	void					Trash();
	void					RemoveFromParent();

	void					ParseAttribute(const TiXmlAttribute* attribute);
	void					ParseAttributes(const TiXmlElement* element);


private:

	std::string					m_name;

	bool						m_enabled;
	bool						m_dirty;
	bool						m_trashed;
	bool						m_justEnabled;

	Vector2f					m_pos;
	Vector2f					m_scale;
	Vector2f					m_origin;

	float						m_rotation;

	sf::Transformable			m_transformable;
	sf::Transformable			m_globalTransformable;

	ObjectRef					m_parent;

	std::vector<ObjectPtr>		m_children;
	std::vector<ComponentPtr>	m_components;

};