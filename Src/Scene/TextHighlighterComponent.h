#pragma once

#include "Component.h"
#include "stdincl.h"

class TextHighlighterComponent : public Component
{
	REGISTER(TextHighlighterComponent);

public:

	TextHighlighterComponent(void);
	~TextHighlighterComponent(void);

	void							OnStart();
	void							Update(float dtime);

	void							Select();
	void							UnSelect();

private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;
	void							CheckMouseCollision();

	Vector3f						m_highlightedColorMask;

	ObjectRef						m_spriteHolder;

	bool							m_selected;



};		

