#pragma once

#include "Component.h"
#include "stdincl.h"

class PlayerHpBar : public Component
{
	REGISTER(PlayerHpBar);

public:

	PlayerHpBar(void);
	~PlayerHpBar(void);

	virtual void					OnAddToObject() override;

	virtual void					Update(float dtime) override;

	void							SetTexture(const std::string &target, const std::string &filename);
	void							SetOffset(const std::string &target, Vector2f offset);
	void							SetPlayer(ObjectRef player);

	void							SetFeedback();
	void							LoadTextures();

private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	int								m_lastHp;

	ObjectRef						m_player;

	ObjectRef						m_avatar;
	ObjectRef						m_frame;
	ObjectRef						m_greenBar;

	std::string						m_avatarTextureFile;
	std::string						m_frameTextureFile;
	std::string						m_greenBarTextureFile;

	Vector2f						m_barSize;

	Vector2f						m_avatarOffset;
	Vector2f						m_barOffset;

};		

