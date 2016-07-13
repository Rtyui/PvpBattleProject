#include "FrozenOrb.h"
#include "stdincl.h"
#include "StunEffect.h"
#include "Object.h"
#include "RangedAttackSpell.h"
#include "CharacterComponent.h"
#include "ProjectileComponent.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "App.h"

FrozenOrb::FrozenOrb()
{
	Spell::Spell();
	type = PROJECTILE_APPLY_ON_CHARACTER;

	damage = FROZEN_ORB_DAMAGE;
	cooldown = FROZEN_ORB_COOLDOWN;
	projectileSpeed = FROZEN_ORB_PROJECTILE_SPEED;
	stun_duration = FROZEN_ORB_STUN_DURATION;
}

FrozenOrb::~FrozenOrb() 
{
}

void FrozenOrb::Cast(ObjectRef user, ObjectRef enemy)
{
	r_cooldown = cooldown;


	auto projectileObject = Object::Create();

	projectileObject->SetJustEnabled();

	static int projectileNumber = 0;
	std::string name = std::string("projectile") + std::to_string(projectileNumber++);
	projectileObject->SetName(name);

	auto projectileComp = projectileObject->AddComponent<ProjectileComponent>();
	auto spriteComp = projectileObject->AddComponent<SpriteComponent>();
	auto colliderComp = projectileObject->AddComponent<ColliderComponent>();

	Vector2f direction = Vector2f(0, -1);

	projectileComp->SetDirection(direction);
	projectileComp->SetSpeed(projectileSpeed);
	projectileComp->SetSpell(this);
	projectileComp->SetUser(user);
	projectileComp->SetCanReflect(true);

	spriteComp->SetTexture("frozen_orb.png");
	spriteComp->SetSize(Vector2f(40, 40));

	colliderComp->InitShape("rectangle", "20, 20");
	colliderComp->SetIsStatic(false);
	colliderComp->SetIsPhantom(true);

	projectileObject->SetPos(user->GetPos() +
		Vector2f(user->GetComponent<SpriteComponent>()->GetSize().x / 2, 25));
	g_menuHandler->GetCurrentMenu()->AddChild(std::move(projectileObject));
}

void FrozenOrb::Apply(ObjectRef target)
{
	auto characterComp = target->GetComponent<CharacterComponent>();

	if (!characterComp)
		return;

	auto character = characterComp->GetCharacter();

	character->TakeDamage(damage);

	EffectRef sEffect = new StunEffect();
	sEffect->SetDuration(stun_duration);
	sEffect->Apply(character);
	
}