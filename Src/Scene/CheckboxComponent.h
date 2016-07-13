#pragma once

#include "Component.h"
#include "stdincl.h"
#include "ButtonComponent.h"

class CheckboxComponent : public Component
{
	REGISTER(CheckboxComponent);

public:

	enum STATES { FOCUSED, UNFOCUSED, NUM_STATES};

	CheckboxComponent(void);
	~CheckboxComponent(void);

	virtual void					OnAddToObject() override;
	virtual void					Update(float dtime) override;

	void							SetSize(Vector2f size);
	void							SetTexture(uint state, const std::string &filename);
	void							SetCheckSprite(const std::string& checkSprite);
	void							Toggle();
	void							Focus();
	void							Unfocus();

	bool							IsSelected();


private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	void							Select();
	void							UnSelect();
	void							CheckMouseCollision();

	void							AddSprite();
	void							AddCheck();

	Vector2f						m_size;

	std::string						m_textures[NUM_STATES];

	bool							m_selected;
	bool							m_focused;
	
	std::string						m_checkSprite;
	
	ObjectRef						m_checkObject;
	ObjectRef						m_stateObjects[NUM_STATES];



};		

