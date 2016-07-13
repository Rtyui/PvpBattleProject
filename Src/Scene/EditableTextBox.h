#pragma once

#include "Component.h"
#include "stdincl.h"


class EditableTextBox : public Component
{
	REGISTER(EditableTextBox);

public:

	enum STATES { SELECTED, UNSELECTED, NUM_STATES };

	EditableTextBox(void);
	~EditableTextBox(void);

	void							OnAddToObject() override;
	void							Update(float dtime) override;

	void							CreateObjects();

	void							CheckMouseCollision();

	void							SetSize(Vector2f size);
	void							SetFont(const std::string& font);
	void							SetFontSize(uint size);
	void							SetTextureSelected(const std::string& texture);
	void							SetTextureUnselected(const std::string& texture);
	void							SetTextMaxLength(uint maxLength);
	void							SetTextColor(Vector3f color);

	void							ClearText();

	std::string						GetText();

	void							Select();
	void							UnSelect();

	void							AddCharacter();
	void							DeleteLastCharacter();

private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	Vector2f						m_size;

	std::string						m_textures[NUM_STATES];
	std::string						m_font;

	uint							m_fontSize;

	ObjectRef						m_spritesHolders[NUM_STATES];
	ObjectRef						m_textHolder;

	bool							m_selected;

	uint							m_textMaxLength;

	Vector3f						m_textColor;
};		

