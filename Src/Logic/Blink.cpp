#include "Blink.h"
#include "stdincl.h"

#include "Object.h"
#include "RangedAttackSpell.h"
#include "CharacterComponent.h"
#include "ProjectileComponent.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "App.h"

Blink::Blink()
{
	cooldown = BLINK_COOLDOWN;
	moveDistance = BLINK_MOVE_DISTANCE;
}

Blink::~Blink()
{
}

void Blink::Cast(ObjectRef user, ObjectRef enemy)
{
	r_cooldown = cooldown;

	auto dComp = user->GetComponent<PlayerMovement>();
	Vector2f direction = dComp->GetDirection();

	user->SetPos(user->GetPos() + direction * moveDistance);
}

void Blink::Apply(ObjectRef target)
{
}