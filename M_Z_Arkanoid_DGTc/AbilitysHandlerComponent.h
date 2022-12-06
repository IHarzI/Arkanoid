#pragma once
#include "Component.h"

class AbilitysHandlerComponent :
    public Component
{
public:
    AbilitysHandlerComponent() {}
    ~AbilitysHandlerComponent() { m_abilitysHandled.clear(); }

    virtual void update(BaseEntity* player, GameWorld* gameworld, double ts) override;

    void AddAbility(EntityType type);

    void clear() { m_abilitysHandled.clear(); }

private:
    List(Scope(HandledAbility)) m_abilitysHandled;

};

