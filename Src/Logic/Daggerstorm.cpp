#include "SlowEffect.h"
#include "DotEffect.h"
#include "Daggerstorm.h"
#include "stdincl.h"

#include "Object.h"
#include "RangedAttackSpell.h"
#include "CharacterComponent.h"
#include "ProjectileComponent.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "App.h"

Daggerstorm::Daggerstorm()
{
	type = PROJECTILE_APPLY_ON_CHARACTER;
	cooldown = DAGGERSTORM_COOLDOWN;
	damage = DAGGERSTORM_DAMAGE;
	projectileSpeed = DAGGERSTORM_PROJECTILE_SPEED;
	slowPercentage = DAGGERSTORM_SLOW_PERCENTAGE;
	damageOverTime = DAGGERSTORM_DAMAGE_OVER_TIME;
	duration = DAGGERSTORM_DURATION;
	directions.push_back(Vector2f(0, -1));
	directions.push_back(Vector2f(1, -1));
	directions.push_back(Vector2f(1, 0));
	directions.push_back(Vector2f(1, 1));
	directions.push_back(Vector2f(0, 1));
	directions.push_back(Vector2f(-1, -1));
	directions.push_back(Vector2f(-1, 0));
	directions.push_back(Vector2f(-1, 1));
}

Daggerstorm::~Daggerstorm() 
{
}

void Daggerstorm::Cast(ObjectRef user, ObjectRef enemy)
{
	for (int i = 0; i < 8; i++) {
		auto projectileObject = Object::Create();

		projectileObject->SetJustEnabled();

		static int projectileNumber = 0;
		std::string name = std::string("projectile") + std::to_string(projectileNumber++);
		projectileObject->SetName(name);

		auto projectileComp = projectileObject->AddComponent<ProjectileComponent>();
		auto spriteComp = projectileObject->AddComponent<SpriteComponent>();
		auto colliderComp = projectileObject->AddComponent<ColliderComponent>();

		Vector2f direction = directions[i];

		projectileComp->SetDirection(direction);
		projectileComp->SetSpeed(projectileSpeed);
		projectileComp->SetSpell(this);
		projectileComp->SetUser(user);
		projectileComp->SetCanApplyOnUser(false);

		spriteComp->SetTexture("dagger.png");
		spriteComp->SetSize(Vector2f(20, 40));

		colliderComp->InitShape("rectangle", "20, 20");
		colliderComp->SetIsStatic(false);
		colliderComp->SetIsPhantom(true);

		Vector2f userPos = user->GetComponent<SpriteComponent>()->GetSize();
		Vector2f startingPos = user->GetPos() + userPos/2.f;
		Vector2f projectileSize = spriteComp->GetSize();
		float magic = (sqrt(pow(projectileSize.x, 2) + pow(projectileSize.y, 2))) / 2;

		projectileObject->SetPos(startingPos +
			magic * direction);
		g_menuHandler->GetCurrentMenu()->AddChild(std::move(projectileObject));
	}

	r_cooldown = cooldown;

}

void Daggerstorm::Apply(ObjectRef target)
{
	auto characterComp = target->GetComponent<CharacterComponent>();

	if (!characterComp)
		return;

	auto character = characterComp->GetCharacter();

	Effect *sEffect = new SlowEffect();
	((SlowEffect *)sEffect)->SetPercentage(slowPercentage / 100.f);
	sEffect->SetDuration(duration);

	Effect *dEffect = new DotEffect();
	((DotEffect *)dEffect)->SetDamage(damageOverTime);
	dEffect->SetDuration(duration);

	sEffect->Apply(characterComp->GetCharacter());
	dEffect->Apply(characterComp->GetCharacter());
}