#pragma once

#include "Component.h"
#include "stdincl.h"

enum STATES { SELECTED, UNSELECTED, NUM_STATES };

class ButtonCheckedBox : public Component
{
	REGISTER(ButtonCheckedBox);

public:

	ButtonCheckedBox(void);
	~ButtonCheckedBox(void);

	void							SetSize(Vector2f size);
	void							SetPos(Vector2f position);
	void							SetTexture(uint state, const std::string &filename);

	void							Select();
	void							UnSelect();

private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	Vector2f						m_size;
	Vector2f						m_position;

	sf::Texture						m_textures[NUM_STATES];

	ObjectRef						m_spriteHolder;

	bool							m_selected;



};		

