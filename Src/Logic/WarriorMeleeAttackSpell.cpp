#include "WarriorMeleeAttackSpell.h"
#include "PlayerMovement.h"
#include "CharacterComponent.h"


WarriorMeleeAttackSpell::WarriorMeleeAttackSpell()
{
	Spell::Spell();
	type = MELEE;
	aoe = WARRIOR_MELEE_ATTACK_AOE;
	damage = WARRIOR_MELEE_ATTACK_DAMAGE;
	slowPercentage = WARRIOR_MELEE_SLOW_PERCENTAGE;
	cooldown = WARRIOR_MELEE_ATTACK_COOLDOWN;
}

WarriorMeleeAttackSpell::~WarriorMeleeAttackSpell()
{

}

void WarriorMeleeAttackSpell::Cast(ObjectRef user, ObjectRef enemy)
{
	r_cooldown = cooldown;
	Vector2f direction = user->GetComponent<PlayerMovement>()->GetDirection();

	Vector2f userPos = user->GetPos();
	Vector2f enemyPos = enemy->GetPos();

	Vector2f newPos = userPos + Vector2f(2 * direction.x, 2 * direction.y);
	double firstDistance = sqrt( pow((userPos.x - enemyPos.x), 2)
										+ pow((userPos.y - enemyPos.y), 2));
	double secondDistance = sqrt(pow((newPos.x - enemyPos.x), 2)
										+ pow((newPos.y - enemyPos.y), 2));

	if (secondDistance < firstDistance && firstDistance < aoe)
	{
		Apply(enemy);
	}
}

void WarriorMeleeAttackSpell::Apply(ObjectRef target)
{
	auto characterComp = target->GetComponent<CharacterComponent>();

	if (!characterComp)
		return;

	auto character = characterComp->GetCharacter();

	character->TakeDamage(damage);
}