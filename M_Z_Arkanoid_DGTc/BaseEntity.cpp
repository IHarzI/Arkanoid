#include "BaseEntity.h"

Pair(bool, BaseEntity*) BaseEntity::IsCollided(BaseEntity* entity)
{
    if (entity->GetRightBound().x_ >= GetLeftBound().x_ && entity->GetLeftBound().x_ <= GetRightBound().x_
        && entity->GetUpBound().y_<=GetDownBound().y_ && entity->GetDownBound().y_>=GetUpBound().y_)
    {
        return MakePair(true, this);
    }
    return MakePair(false, nullptr);

}
