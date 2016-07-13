#pragma once

#include "Component.h"
#include "stdincl.h"
#include "ConsoleInputHandler.h"
#include "ConsoleCommandsHandler.h"

class ConsoleComponent : public Component
{
	REGISTER(ConsoleComponent);

public:

	ConsoleComponent(void);
	~ConsoleComponent(void);

	virtual void					OnAddToObject() override;
	virtual void					Update(float dtime) override;
	virtual void					PostUpdate(float dtime) override;

	void							SetLineSize(float lineSize);
	void							SetTextSize(uint textSize);
	void							SetFont(const std::string& font);
	void							CreateLinesObjects();
	void							CreateCommand(const std::string& commandName, function f);

	void							ShiftLines();
	void							WriteMessage(const std::string& message);

	
private:

	void							SubmitCommand();
	void							DeleteLastCharacter();
	void							PredictCommand();

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	std::vector<ObjectRef>			m_consoleLines;

	ObjectRef						m_consoleCommandLine;

	static float					m_lineSize;
	static uint						m_textSize;
	static std::string				m_font;

	ConsoleInputHandler				m_consoleInputHandler;
	ConsoleCommandsHandler			m_consoleCommandsHandler;
};