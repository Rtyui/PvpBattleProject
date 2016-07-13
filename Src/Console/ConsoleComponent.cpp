#include "ConsoleComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

float			ConsoleComponent::m_lineSize;
uint			ConsoleComponent::m_textSize;
std::string		ConsoleComponent::m_font;

REGISTERIMPL(ConsoleComponent);

ConsoleComponent::ConsoleComponent()
{
}

ConsoleComponent::~ConsoleComponent()
{
}

void ConsoleComponent::OnAddToObject()
{
	auto spriteComp = m_object->GetComponent<SpriteComponent>();
	assert(spriteComp);

	spriteComp->SetSize(Vector2f((float)g_app->APP_RESOLUTION_WIDTH, (float)g_app->APP_RESOLUTION_HEIGHT * 3.f / 4.f));
	spriteComp->SetAlpha(180);

	CreateLinesObjects();
}

void ConsoleComponent::Update(float dtime)
{
	if (g_input->WasKeyPressed())
	{
		m_consoleInputHandler.UpdateCommandLine(g_input->KeyPressed(), m_consoleCommandLine);
	}

	if (g_input->WasPressedThisTurn(KEY_RETURN))
	{
		SubmitCommand();
	}

	if (g_input->WasPressedThisTurn(KEY_BACKSPACE))
	{
		DeleteLastCharacter();
	}

	if (g_input->WasPressedThisTurn(KEY_TAB))
	{
		PredictCommand();
	}
}

void ConsoleComponent::PostUpdate(float dtime)
{
}

void ConsoleComponent::SetLineSize(float lineSize)
{
	m_lineSize = lineSize;
}

void ConsoleComponent::SetTextSize(uint textSize)
{
	m_textSize = textSize;
}

void ConsoleComponent::SetFont(const std::string& font)
{
	m_font = font;
}

void ConsoleComponent::CreateLinesObjects()
{
	float consoleHeight = g_app->APP_RESOLUTION_HEIGHT * 3.f / 4.f;	
	uint lineNumbers = (uint)(consoleHeight / m_lineSize) - 1;

	for (uint i = 0; i < lineNumbers; ++i)
	{
		auto lineObject = Object::Create();
		auto textComp = lineObject->AddComponent<TextComponent>();

		textComp->SetFont(m_font);
		textComp->SetFontSize(m_textSize);

		lineObject->SetPos(Vector2f(0.f, i * m_lineSize));

		m_consoleLines.push_back(lineObject.get());
		m_object->AddChild(std::move(lineObject));
	}

	auto commandLineObject = Object::Create();
	auto textComp = commandLineObject->AddComponent<TextComponent>();

	textComp->SetFont(m_font);
	textComp->SetFontSize(m_textSize);

	commandLineObject->SetPos(Vector2f(0.f, m_consoleLines[m_consoleLines.size() - 1]->GetPos().y + m_lineSize));
	m_consoleCommandLine = commandLineObject.get();
	m_object->AddChild(std::move(commandLineObject));
}

void ConsoleComponent::CreateCommand(const std::string& commandName, function f)
{
	m_consoleCommandsHandler.CreateCommand(commandName, f);
}

void ConsoleComponent::ShiftLines()
{
	for (uint i = 0; i < m_consoleLines.size() - 1; ++i)
	{
		auto currTextComp = m_consoleLines[i]->GetComponent<TextComponent>();
		assert(currTextComp);

		auto nextTextComp = m_consoleLines[i + 1]->GetComponent<TextComponent>();
		assert(nextTextComp);

		currTextComp->SetText(nextTextComp->GetText());
	}
}

void ConsoleComponent::SubmitCommand()
{
	auto lastLineTextComp = m_consoleLines[m_consoleLines.size() - 1]->GetComponent<TextComponent>();
	assert(lastLineTextComp);

	auto commandLineTextComp = m_consoleCommandLine->GetComponent<TextComponent>();
	assert(commandLineTextComp);

	ShiftLines();
	m_consoleCommandsHandler.HandleCommand(commandLineTextComp->GetText(), lastLineTextComp);
	
	commandLineTextComp->SetText("");
}

void ConsoleComponent::DeleteLastCharacter()
{
	auto commandLineTextComp = m_consoleCommandLine->GetComponent<TextComponent>();
	assert(commandLineTextComp);

	std::string s = commandLineTextComp->GetText();
	if (s.size() > 0)
	{
		s.resize(s.size() - 1);
	}
	commandLineTextComp->SetText(s);
}

void ConsoleComponent::PredictCommand()
{
	auto lastLineTextComp = m_consoleCommandLine->GetComponent<TextComponent>();
	m_consoleCommandsHandler.PredictCommand(lastLineTextComp);
}

void ConsoleComponent::WriteMessage(const std::string& message)
{
	ShiftLines();

	auto lastLineTextComp = m_consoleLines[m_consoleLines.size() - 1]->GetComponent<TextComponent>();
	assert(lastLineTextComp);

	lastLineTextComp->SetText(message);
}

void ConsoleComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	Component::ParseAttribute(attribute);
	if (IsEqual(attribute->Name(), "line_size"))
	{
		SetLineSize(attribute->FloatValue());
	}

	else if (IsEqual(attribute->Name(), "text_size"))
	{
		SetTextSize(attribute->UnsignedValue());
	}

	else if (IsEqual(attribute->Name(), "text_font"))
	{
		SetFont(attribute->Value());
	}

}

