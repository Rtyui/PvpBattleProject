#include "RangedAttackSpell.h"
#include "CharacterComponent.h"
#include "ProjectileComponent.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "App.h"

RangedAttackSpell::RangedAttackSpell()
{
	Spell::Spell();
	type = PROJECTILE_APPLY_ON_CHARACTER;
	damage = RANGED_ATTACK_DAMAGE;
	projectileSpeed = BASE_PROJECTILE_SPEED;
	slowPercentage = RANGED_ATTACK_SLOW_PERCENTAGE;
	cooldown = RANGED_ATTACK_COOLDOWN;
}

RangedAttackSpell::~RangedAttackSpell() {}

void RangedAttackSpell::Cast(ObjectRef user, ObjectRef enemy)
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
	Vector2f direction = user->GetComponent<PlayerMovement>()->GetDirection();

	projectileComp->SetDirection(direction);
	projectileComp->SetSpeed(projectileSpeed);
	projectileComp->SetSpell(this);
	projectileComp->SetUser(user);

	spriteComp->SetTexture("fireball.png");
	spriteComp->SetSize(Vector2f(40, 40));

	colliderComp->InitShape("rectangle", "20, 20");
	colliderComp->SetIsStatic(false);
	colliderComp->SetIsPhantom(true);

	projectileObject->SetPos(user->GetPos() + Vector2f((direction.x == 1 ? user->GetComponent<SpriteComponent>()->GetSize().x : -20.f), 0));
	g_menuHandler->GetCurrentMenu()->AddChild(std::move(projectileObject));
}

void RangedAttackSpell::Apply(ObjectRef target)
{
	auto characterComp = target->GetComponent<CharacterComponent>();

	if (!characterComp)
		return;

	auto character = characterComp->GetCharacter();

	character->TakeDamage(damage);
}