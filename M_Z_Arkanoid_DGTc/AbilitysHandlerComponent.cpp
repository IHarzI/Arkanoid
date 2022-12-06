#include "AbilitysHandlerComponent.h"
#include "PlayerEntity.h"


#define MaxBoost 1.4
#define MinBoost 0.6

#define Boost 0.15

bool IsActive(Scope(HandledAbility) ability) { return (ability->lifetime_ <= 0); }

void AbilitysHandlerComponent::update(BaseEntity* player, GameWorld* gameworld, double ts)
{

	float mod = 1;
	for (auto abiliti = m_abilitysHandled.begin(); abiliti != m_abilitysHandled.end(); abiliti++)
	{
		if ((*abiliti)->type_==POSITIVE_ABILITY)
			mod += Boost;
		else if((*abiliti)->type_ == NEGATIVE_ABILITY)
			mod -= Boost;
		(*abiliti)->update(ts);
	}
	if (mod > MaxBoost)
		mod = MaxBoost;
	else if (mod < MinBoost)
		mod = MinBoost;

	((PlayerEntity*)player)->updateAbilitiModifier(mod);

	m_abilitysHandled.remove_if(IsActive);
}

void AbilitysHandlerComponent::AddAbility(EntityType type)
{

	m_abilitysHandled.push_back(CreateScope(HandledAbility,type));
}
