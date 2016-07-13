#pragma once

#include "Component.h"
#include "stdincl.h"

class PlayerMovement : public Component
{
	REGISTER(PlayerMovement);

public:

	PlayerMovement(void);
	~PlayerMovement(void);

	virtual void					Update(float dtime) override;

	void							SetOnGround(bool value);
	void							SetVerticalVelocity(float value);
	void							SetControls(int controls);

	void							SwitchSide();

	float							GetVerticalVelocity();
	Vector2f						GetDirection();
	

private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	int								m_controlsSet;
	Vector2f						m_direction;

	float							m_verticalVelocity;
	bool							m_onGround;

	static float					m_jumpPower;
};		

