/* Arsenescu Mihai-Catalin - IP 2015
**/
#pragma once

#include "Component.h"
#include "stdincl.h"

class PlayMenu : public Component
{
	REGISTER(PlayMenu);
public:
	PlayMenu(void);
	~PlayMenu(void);

	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;
	virtual void			OnStart() override;
	void					AddCharacterToGameSession();

private:

	std::vector<ObjectRef> leftObj;
	std::vector<ObjectRef> leftDescriptions;
	std::vector<ObjectRef> rightObj;
	std::vector<ObjectRef> rightDescriptions;

	int indexL;
	int indexR;


};

