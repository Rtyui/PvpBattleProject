#include "PlayMenu.h"
#include "App.h"
#include "stdincl.h"
#include "Object.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "CharacterComponent.h"
#include "PlayerMovement.h"
#include "PlayerHpBar.h"
#include "SpellFeedbackComponent.h"

REGISTERIMPL(PlayMenu);

PlayMenu::PlayMenu()
{
	// 206 500
	// 806 1100
	
}

void PlayMenu::OnStart()
{
	char *textures[3] = { "wizard.png", "warrior.png", "assassin.png" };
	char *descriptions[3] = { "wizard_spells.png", "warrior_spells.png", "assassin_spells.png" };

	for (int i = 0; i < 3; i++) {
		auto obj = Object::Create();
		obj->SetPos(Vector2f(206, 250));
		obj->SetEnabled(i ? 0 : 1);

		auto comp = obj->AddComponent<SpriteComponent>();
		comp->SetTexture(textures[i]);
		comp->SetSize(Vector2f(300, 400));

		leftObj.push_back(obj.get());
		m_object->AddChild(std::move(obj));

		auto obj2 = Object::Create();
		obj2->SetPos(Vector2f(156, 0));
		obj2->SetEnabled(i ? 0 : 1);

		comp = obj2->AddComponent<SpriteComponent>();
		comp->SetTexture(descriptions[i]);
		comp->SetSize(Vector2f(450, 250));

		leftDescriptions.push_back(obj2.get());
		m_object->AddChild(std::move(obj2));

		auto obj3 = Object::Create();
		obj3->SetPos(Vector2f(806, 250));
		obj3->SetEnabled(i ? 0 : 1);

		comp = obj3->AddComponent<SpriteComponent>();
		comp->SetTexture(textures[i]);
		comp->SetSize(Vector2f(300, 400));

		rightObj.push_back(obj3.get());
		m_object->AddChild(std::move(obj3));

		auto obj4 = Object::Create();
		obj4->SetPos(Vector2f(756, 0));
		obj4->SetEnabled(i ? 0 : 1);

		comp = obj4->AddComponent<SpriteComponent>();
		comp->SetTexture(descriptions[i]);
		comp->SetSize(Vector2f(450, 250));

		rightDescriptions.push_back(obj4.get());
		m_object->AddChild(std::move(obj4));
	}

	indexL = 0;
	indexR = 0;
}

PlayMenu::~PlayMenu()
{
}

void PlayMenu::Update(float dtime)
{
	char *buttonNames[4] = {"LeftButton1", "RightButton1", "LeftButton2", "RightButton2"};

	auto bObj = m_object->FindChild(buttonNames[0]);
	auto bComp = bObj->GetComponent<ButtonComponent>();
	if (bComp->WasPressed()) {
		leftObj[indexL]->SetEnabled(false);
		leftDescriptions[indexL]->SetEnabled(false);
		indexL = (indexL == 0) ? 2 : (indexL - 1);
		leftObj[indexL]->SetEnabled(true);
		leftDescriptions[indexL]->SetEnabled(true);
	}

	bObj = m_object->FindChild(buttonNames[1]);
	bComp = bObj->GetComponent<ButtonComponent>();
	if (bComp->WasPressed()) {
		leftObj[indexL]->SetEnabled(false);
		leftDescriptions[indexL]->SetEnabled(false);
		indexL = (indexL == 2) ? 0 : (indexL + 1);
		leftObj[indexL]->SetEnabled(true);
		leftDescriptions[indexL]->SetEnabled(true);
	}

	bObj = m_object->FindChild(buttonNames[2]);
	bComp = bObj->GetComponent<ButtonComponent>();
	if (bComp->WasPressed()) {
		rightObj[indexR]->SetEnabled(false);
		rightDescriptions[indexR]->SetEnabled(false);
		indexR = (indexR == 0) ? 2 : (indexR - 1);
		rightObj[indexR]->SetEnabled(true);
		rightDescriptions[indexR]->SetEnabled(true);
	}

	bObj = m_object->FindChild(buttonNames[3]);
	bComp = bObj->GetComponent<ButtonComponent>();
	if (bComp->WasPressed()) {
		rightObj[indexR]->SetEnabled(false);
		rightDescriptions[indexR]->SetEnabled(false);
		indexR = (indexR == 2) ? 0 : (indexR + 1);
		rightObj[indexR]->SetEnabled(true);
		rightDescriptions[indexR]->SetEnabled(true);
	}

	bObj = m_object->FindChild("Play");
	bComp = bObj->GetComponent<ButtonComponent>();
	if (bComp->WasPressed()) {
		AddCharacterToGameSession();
		g_menuHandler->SwitchMenu(MAIN_GAME);
	}
}

void PlayMenu::PostUpdate(float dtime)
{
}

void PlayMenu::AddCharacterToGameSession()
{
	char *player[3] = { "PlayerWizard.xml", "PlayerWarrior.xml", "PlayerAssassin.xml" };
	char *hpBars[3] = { "HpBarWizard.xml", "HpBarWarrior.xml", "HpBarAssassin.xml" };
	char *playersNames[3] = { "wizard", "warrior", "assassin" };

	auto player1 = Object::CreateFromFile(player[indexL]);
	auto player2 = Object::CreateFromFile(player[indexR]);

	player1->SetPos(Vector2f(384, 450));
	player2->SetPos(Vector2f(896, 450));

	player1->GetComponent<PlayerMovement>()->SetControls(0);
	player2->GetComponent<PlayerMovement>()->SetControls(1);

	auto player1CharComp = player1->GetComponent<CharacterComponent>();
	auto player2CharComp = player2->GetComponent<CharacterComponent>();

	player1CharComp->SetEnemy(player2.get());
	player2CharComp->SetEnemy(player1.get());

	player1CharComp->SetControls(0);
	player2CharComp->SetControls(1);

	auto hpBar1 = Object::CreateFromFile(hpBars[indexL]);
	auto hpBar2 = Object::CreateFromFile(hpBars[indexR]);

	hpBar1->SetName("LeftHpBar");
	hpBar2->SetName("RightHpBar");

	hpBar1->SetPos(Vector2f(0, 0));
	hpBar2->SetPos(Vector2f(g_app->APP_RESOLUTION_WIDTH - 200, 0));

	hpBar1->GetComponent<PlayerHpBar>()->SetPlayer(player1.get());
	hpBar2->GetComponent<PlayerHpBar>()->SetPlayer(player2.get());

	auto spellBar1 = Object::Create();
	auto spellBar2 = Object::Create();

	spellBar1->SetPos(Vector2f(0.f, 685.f));
	spellBar2->SetPos(Vector2f(1175.f, 685.f));

	auto spellBar1Comp = spellBar1->AddComponent<SpellFeedbackComponent>();
	auto spellBar2Comp = spellBar2->AddComponent<SpellFeedbackComponent>();

	spellBar1Comp->SetCharacter(playersNames[indexL]);
	spellBar2Comp->SetCharacter(playersNames[indexR]);

	spellBar1Comp->SetCharacter(player1CharComp->GetCharacter());
	spellBar2Comp->SetCharacter(player2CharComp->GetCharacter());

	auto mainGameObject = g_menuHandler->GetMenuObject(MAIN_GAME);

	mainGameObject->AddChild(std::move(player1));
	mainGameObject->AddChild(std::move(player2));
	mainGameObject->AddChild(std::move(hpBar1));
	mainGameObject->AddChild(std::move(hpBar2));
	mainGameObject->AddChild(std::move(spellBar1));
	mainGameObject->AddChild(std::move(spellBar2));
}