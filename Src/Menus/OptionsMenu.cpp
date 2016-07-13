#include "OptionsMenu.h"
#include "App.h"
#include "stdincl.h"
#include "CheckboxComponent.h"
#include "ButtonComponent.h"

REGISTERIMPL(OptionsMenu);

OptionsMenu::OptionsMenu()
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::OnStart()
{
	Preset();
}

void OptionsMenu::Update(float dtime)
{
	CheckIfApplied();
	CheckIfCanceled();
}

void OptionsMenu::PostUpdate(float dtime)
{
}

void OptionsMenu::Apply()
{
	auto fullscreenCheckBoxObject = m_object->FindChild("FullscreenCheckbox");
	assert(fullscreenCheckBoxObject);

	auto fullscreenCheckBoxComponent = fullscreenCheckBoxObject->GetComponent<CheckboxComponent>();
	assert(fullscreenCheckBoxComponent);

	if (fullscreenCheckBoxComponent->IsSelected() != g_optionsManager->m_fullscreen)
	{
		g_optionsManager->m_fullscreen = fullscreenCheckBoxComponent->IsSelected();
		g_optionsManager->RefreshWindow();
	}
}

void OptionsMenu::Cancel()
{
	auto fullscreenCheckBoxObject = m_object->FindChild("FullscreenCheckbox");
	assert(fullscreenCheckBoxObject);

	auto fullscreenCheckBoxComponent = fullscreenCheckBoxObject->GetComponent<CheckboxComponent>();
	assert(fullscreenCheckBoxComponent);

	if (fullscreenCheckBoxComponent->IsSelected() != g_optionsManager->m_fullscreen)
	{
		fullscreenCheckBoxComponent->Toggle();
	}
}

void OptionsMenu::CheckIfApplied()
{
	auto applyButtonObject = m_object->FindChild("ApplyButton");
	assert(applyButtonObject);

	auto applyButtonComponent = applyButtonObject->GetComponent<ButtonComponent>();
	assert(applyButtonComponent);

	if (applyButtonComponent->WasPressed())
	{
		Apply();
		g_menuHandler->SwitchMenu(MAIN_MENU);
	}
}

void OptionsMenu::CheckIfCanceled()
{
	auto cancelButtonObject = m_object->FindChild("CancelButton");
	assert(cancelButtonObject);

	auto cancelButtonComponent = cancelButtonObject->GetComponent<ButtonComponent>();
	assert(cancelButtonComponent);

	if (cancelButtonComponent->WasPressed())
	{
		Cancel();
		g_menuHandler->SwitchMenu(MAIN_MENU);
	}
}

void OptionsMenu::Preset()
{
	auto fullscreenCheckBoxObject = m_object->FindChild("FullscreenCheckbox");
	assert(fullscreenCheckBoxObject);

	auto fullscreenCheckBoxComponent = fullscreenCheckBoxObject->GetComponent<CheckboxComponent>();
	assert(fullscreenCheckBoxComponent);

	if (fullscreenCheckBoxComponent->IsSelected() != g_optionsManager->m_fullscreen)
	{
		fullscreenCheckBoxComponent->Toggle();
	}
}