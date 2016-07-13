#include "Object.h"
#include "Helpers.h"
#include "ObjectHelpers.h"
#include "ComponentFactory.h"
#include "SpriteComponent.h"

Object::Object() :
m_enabled(true),
m_scale(Vector2f(1.f, 1.f)),
m_dirty(true),
m_trashed(false),
m_justEnabled(false)
{
}

Object::~Object()
{
}

void Object::OnStart()
{
	for (uint i = 0; i < m_components.size(); ++i)
	{
		auto comp = m_components[i].get();
		comp->OnStart();
	}
	for (uint i = 0; i < m_children.size(); ++i)
	{
		auto child = m_children[i].get();
		child->OnStart();
	}
}

void Object::OnActivate()
{
	for (uint i = 0; i < m_components.size(); ++i)
	{
		auto comp = m_components[i].get();
		comp->OnActivate();
	}
	for (uint i = 0; i < m_children.size(); ++i)
	{
		auto child = m_children[i].get();
		child->OnActivate();
	}
}

void Object::Update(float dtime)
{
	
	for (uint i = 0; i < m_components.size(); ++i)
	{
		auto comp = m_components[i].get();
		comp->Update(dtime);
	}

	uint childrenSize = m_children.size();
	std::vector<bool> updatables(childrenSize, false);
	for (uint i = 0; i < childrenSize; ++i)
	{
		auto child = m_children[i].get();
		updatables[i] = child->IsEnabled();
	}

	for (uint i = 0; i < childrenSize; ++i)
	{
		auto child = m_children[i].get();
		if (updatables[i])
		{
			child->Update(dtime);
		}
	}

	m_justEnabled = false;
}

void Object::PostUpdate(float dtime)
{
	if (m_justEnabled) return;
	if (m_trashed)
	{
		m_parent->RemoveChild(m_name);
	}
	for (uint i = 0; i < m_components.size(); ++i)
	{
		auto comp = m_components[i].get();
		comp->PostUpdate(dtime);
	}

	uint childrenSize = m_children.size();
	std::vector<bool> updatables(childrenSize, false);
	for (uint i = 0; i < childrenSize; ++i)
	{
		auto child = m_children[i].get();
		updatables[i] = child->IsEnabled();
	}
	for (int i = childrenSize - 1; i >= 0; --i)
	{
		auto child = m_children[i].get();
		if (updatables[i])
		{
			child->PostUpdate(dtime);
		}
	}
}

void Object::Draw()
{
	std::vector<bool> updatables(m_children.size(), false);
	for (uint i = 0; i < m_components.size(); ++i)
	{
		m_components[i]->Draw();
	}
	for (uint i = 0; i < m_children.size(); ++i)
	{
		auto child = m_children[i].get();
		updatables[i] = child->IsEnabled();
	}
	for (uint i = 0; i < m_children.size(); ++i)
	{
		auto child = m_children[i].get();
		if (updatables[i])
		{
			child->Draw();
		}
	}
}

ObjectPtr Object::CreateFromFile(const std::string& filename)
{
	std::string file;
	file.append(XML_FOLDER);
	file.append(filename);
	TiXmlDocument doc;
	int ret = doc.LoadFile(file.c_str());
	assert(ret != 0);
	return std::move(CreateFromXML(doc.FirstChildElement()));
}

ObjectPtr Object::CreateFromXML(const TiXmlElement* element)
{
	auto object = CreateObject();
	object->ParseAttributes(element);

	for (auto e = element->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		if (IsEqual(e->Value(), "Object"))
		{
			auto child = CreateFromXML(e);
			object->AddChild(std::move(child));
		}
		else if (ComponentFactory::IsClassDerivedFromComponent(e->Value()))
		{
			auto comp = ComponentFactory::Create(e->Value());
			comp->ParseAttributes(e);
			object->AddComponent(std::move(comp));
		}	
	}
	return std::move(object);
}

ObjectPtr Object::Create()
{
	std::unique_ptr<Object> objPtr = std::make_unique<Object>();
	return std::move(objPtr);
}

void Object::UpdateGTM()
{
	if (m_dirty)
	{
		m_dirty = false;

		m_globalTransformable = m_transformable;

		if (m_parent)
		{
			m_globalTransformable = m_transformable;

			float p_angle = (m_parent->GetRotation()) * (float)PI / 180;
			float angle = m_rotation * (float)PI / 180;

			float px = m_parent->GetTransformable().getPosition().x;
			float py = m_parent->GetTransformable().getPosition().y;

			float x = m_globalTransformable.getPosition().x;
			float y = m_globalTransformable.getPosition().y;

			m_globalTransformable.setPosition(
				Vector2f(x * cos(angle + p_angle) - y * sin(angle + p_angle),
				x * sin(angle + p_angle) + y * cos(angle + p_angle)) +
				Vector2f(px * cos(p_angle) - py * sin(p_angle),
				px * sin(p_angle) + py * cos(p_angle)));

			m_globalTransformable.setRotation(m_globalTransformable.getRotation() + m_parent->GetRotation());

		}
	}
}

std::string Object::GetName()
{
    return m_name;
}

Vector2f Object::GetPos()
{
    return m_pos;
}
Vector2f Object::GetGlobalPos()
{
	UpdateGTM();
	return m_globalTransformable.getPosition();
}

Vector2f Object::GetScale()
{
    return m_scale;
}

Vector2f Object::GetOrigin()
{
	return m_origin;
}

sf::Transform Object::GetTransform()
{
	if (m_parent)
	{
		return m_parent->GetTransform() * m_transformable.getTransform();
	}
	else
	{
		return m_transformable.getTransform();
	}
}

sf::Transformable Object::GetTransformable()
{
	if (m_parent)
	{
		sf::Transformable transformable = m_transformable;

		transformable.setPosition(transformable.getPosition() + m_parent->GetTransformable().getPosition());
		transformable.setRotation(transformable.getRotation() + m_parent->GetTransformable().getRotation());
		transformable.setScale(transformable.getScale() + m_parent->GetTransformable().getScale());

		return transformable;
	}
	else
	{
		return m_transformable;
	}
}

float Object::GetRotation()
{
	if (m_parent)
	{
		return m_rotation + m_parent->GetRotation();
	}
	return m_rotation;
}

float Object::GetGlobalRotation()
{
	UpdateGTM();
	return m_globalTransformable.getRotation();
}

ObjectRef Object::GetParent()
{
    return m_parent;
}

ObjectRef Object::GetChild(uint index)
{
    return m_children[index].get();
}

ObjectRef Object::FindChild(const std::string& name)
{
    for(uint i = 0; i < m_children.size(); ++i)
    {
        if(GetChild(i)->m_name == name)
        {
            return GetChild(i);
        }
    }
    return nullptr;
}

uint Object::AddChild(ObjectPtr&& child)
{
    assert(child);
	child->SetParent(this);
    m_children.push_back(std::move(child));
    return m_children.size() - 1;
}

void Object::InsertChild(ObjectPtr&& child, uint index)
{
	assert(child);
	child->SetParent(this);
	m_children.insert(m_children.begin() + index, std::move(child));
}

void Object::RemoveChild(uint i)
{
	m_children.erase(m_children.begin() + i);
}

void Object::RemoveChild(const std::string& name)
{
	for (uint i = 0; i < m_children.size(); ++i)
	{
		if (IsEqual(GetChild(i)->m_name.c_str(), name.c_str()))
		{
			m_children.erase(m_children.begin() + i);
			return;
		}
	}
}

uint Object::GetChildrenCount()
{
	return m_children.size();
}

void Object::AddComponent(ComponentPtr&& comp)
{
	comp->m_object = this;
	comp->OnAddToObject();
	m_components.push_back(std::move(comp));
}

void Object::Enable()
{
	m_enabled = true;
	OnActivate();
}

void Object::Disable()
{
	m_enabled = false;
}

bool Object::IsEnabled()
{
	return m_enabled;
}

void Object::SetName(std::string name)
{
    m_name = name;
}

void Object::SetEnabled(bool enabled)
{
	m_enabled = enabled;
}

void Object::SetPos(Vector2f pos)
{
    m_pos = pos;
	m_transformable.setPosition(m_pos);
	SetDirty();
}

void Object::SetScale(Vector2f scale)
{
    m_scale = scale;
	m_transformable.setScale(m_scale);
}

void Object::SetOrigin(Vector2f origin)
{
	m_origin = origin;
	m_transformable.setOrigin(m_origin);
}

void Object::SetRotation(float rot)
{
    m_rotation = rot;
	m_transformable.setRotation(m_rotation);
	SetDirty();
}

void Object::SetParent(Object* parent)
{
    m_parent = parent;
}

void Object::SetDirty()
{
	m_dirty = true;
	for (uint i = 0; i < m_children.size(); ++i)
	{
		GetChild(i)->SetDirty();
	}
}

void Object::SetJustEnabled()
{
	m_justEnabled = true;
}

void Object::Trash()
{
	m_trashed = true;
}

void Object::RemoveFromParent()
{
	for (uint i = 0; i < m_parent->m_children.size(); ++i)
	{
		m_parent->RemoveChild(m_name);
	}
}

void Object::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "enabled"))
	{
		SetEnabled(attribute->BoolValue());
	}
	else if (IsEqual(attribute->Name(), "name"))
	{
		SetName(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "pos"))
	{
		SetPos(ParseVector2f(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "scale"))
	{
		SetScale(ParseVector2f(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "rotation"))
	{
		SetRotation(attribute->FloatValue());
	}
}

void Object::ParseAttributes(const TiXmlElement* element)
{
	for (auto a = element->FirstAttribute(); a; a = a->Next())
	{
		ParseAttribute(a);
	}
}