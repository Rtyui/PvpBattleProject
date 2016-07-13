#pragma once

#include "Component.h"
#include "stdincl.h"


class ButtonComponent : public Component
{
	REGISTER(ButtonComponent);

public:

	enum STATES { FOCUSED, UNFOCUSED, NUM_STATES };
	enum TYPES { DEFAULT, MENU_CHANGER, EXIT, NUM_TYPES };
	enum STYLE { DEEP_ON_FOCUS, DEEP_ON_CLICK };

	ButtonComponent(void);
	~ButtonComponent(void);

	virtual void					OnAddToObject() override;
	virtual void					Update(float dtime) override;
	virtual void					PostUpdate(float dtime) override;

	uint							GetTypeIndex(const std::string& type);
	uint							GetStyleIndex(const std::string& style);


	void							SetSize(Vector2f size);
	void							SetTexture(uint state, const std::string &filename);
	void							SetType(uint type);
	void							SetStyle(uint style);
	void							OnFocus();
	void							OnUnfocus();
	void							OnClick();
	void							Deepen();
	void							UnDeepen();
	void							SetPressed(bool clicked);
	void							CheckMouseCollision();
	void							MenuChange();
	void							CreateSpritesObjects();
	void							CreateTextObject();

	void							SetText(const std::string& text);
	void							SetTextFont(const std::string& font);
	void							SetFontSize(uint size);
	void							SetTextColor(Vector3f color);
	void							SetHighlightTextColor(Vector3f color);
	void							SetIfHasTextures(bool hasTextures);
	void							SetIfTextHighlights(bool textHighlights);

	Vector2f						GetSize();

	bool							WasPressed();
	
private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	ObjectRef						m_stateObjects[NUM_STATES];
	ObjectRef						m_textHolder;

	uint							m_type;
	uint							m_style;
	uint							m_fontSize;

	Vector2f						m_size;

	Vector3f						m_textColor;
	Vector3f						m_textHighlight;

	bool							m_wasPressed;
	bool							m_focused;
	bool							m_deepened;

	bool							m_hasTextures;
	bool							m_textHighlights;

	std::string						m_nextMenu;
	std::string						m_textures[NUM_STATES];
	std::string						m_text;
	std::string						m_font;
};		

