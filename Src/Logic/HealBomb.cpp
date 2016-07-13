#include "HealBomb.h"
#include "stdincl.h"

#include "Object.h"
#include "RangedAttackSpell.h"
#include "CharacterComponent.h"
#include "ProjectileComponent.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "App.h"

HealBomb::HealBomb()
{
	type = PROJECTILE_APPLY_ON_CHARACTER;
	damage = HEALBOMB_DAMAGE;
	projectileSpeed = HEALBOMB_PROJECTILE_SPEED;
	slowPercentage = HEALBOMB_SLOW_PERCENTAGE;
	cooldown = HEALBOMB_COOLDOWN;
	heal_percentage = HEALBOMB_HEAL_PERCENTAGE;
}

HealBomb::~HealBomb() 
{
}

void HealBomb::Cast(ObjectRef user, ObjectRef enemy)
{
	auto projectileObject = Object::Create();

	projectileObject->SetJustEnabled();

	static int projectileNumber = 0;
	std::string name = std::string("projectile") + std::to_string(projectileNumber++);
	projectileObject->SetName(name);

	auto projectileComp = projectileObject->AddComponent<ProjectileComponent>();
	auto spriteComp = projectileObject->AddComponent<SpriteComponent>();
	auto colliderComp = projectileObject->AddComponent<ColliderComponent>();

	r_cooldown = cooldown;
	Vector2f direction = Vector2f(0, -1);

	projectileComp->SetDirection(direction);
	projectileComp->SetSpeed(projectileSpeed);
	projectileComp->SetSpell(this);
	projectileComp->SetUser(user);
	projectileComp->SetCanApplyOnUser(true);
	projectileComp->SetCanReflect(true);

	spriteComp->SetTexture("projectile.png");
	spriteComp->SetSize(Vector2f(40, 40));

	colliderComp->InitShape("rectangle", "20, 20");
	colliderComp->SetIsStatic(false);
	colliderComp->SetIsPhantom(true);

	projectileObject->SetPos(user->GetPos() +
		Vector2f(user->GetComponent<SpriteComponent>()->GetSize().x / 2, 
				-user->GetComponent<SpriteComponent>()->GetSize().y));
	g_menuHandler->GetCurrentMenu()->AddChild(std::move(projectileObject));

}

void HealBomb::Apply(ObjectRef target)
{
	auto characterComp = target->GetComponent<CharacterComponent>();

	if (!characterComp)
		return;

	auto character = characterComp->GetCharacter();

	character->HealPercent(heal_percentage);
}