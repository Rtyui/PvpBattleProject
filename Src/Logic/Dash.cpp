#include "Dash.h"
#include "stdincl.h"
#include "Object.h"
#include "CharacterComponent.h"
#include "ColliderComponent.h"
#include "App.h"
#include "DashComponent.h"

Dash::Dash()
{
	Spell::Spell();
	type = PROJECTILE_APPLY_ON_CHARACTER;

	cooldown = DASH_COOLDOWN;
	duration = DASH_DURATION;
	damage = DASH_DAMAGE;
	speed = DASH_SPEED;
	stun_duration = STUN_DURATION;
}

Dash::~Dash() 
{
}

void Dash::Cast(ObjectRef user, ObjectRef enemy)
{
	r_cooldown = cooldown;

	auto dComp = user->GetComponent<DashComponent>();
	if (dComp == NULL) {
		dComp = user->AddComponent<DashComponent>();
	}
	user->GetComponent<CharacterComponent>()->GetCharacter()->SetCanMove(false);
	dComp->SetStun(stun_duration);
	dComp->SetDashSpeed(speed);
	dComp->SetDuration(duration);
	dComp->SetEnabled(true);
	dComp->SetDamage(damage);
}

void Dash::Apply(ObjectRef target)
{
}