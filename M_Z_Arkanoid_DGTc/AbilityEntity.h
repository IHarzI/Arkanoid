#pragma once

#include "BaseEntity.h"
#include "PhysicalComponent.h"
#include "GraphicsComponent.h"


#define PositiveAbilityTexturePath "Textures/PositiveAbility.png"
#define NegativeAbilityTexturePath "Textures/NegativeAbility.png"

class AbilityEntity :
    protected BaseEntity
{
public:
    AbilityEntity()
        : BaseEntity(Coord2D())
    {
        SetType(NEGATIVE_ABILITY);
    };
    virtual void update(GameWorld* gameworld, double ts) override;

    virtual void draw() override;

    void move(int x =0, int y =0) { SetX(x); SetY(y); }

    virtual bool init(GameWorld* gameworld) override;
    
    void Disactivate() { IsActive = false; }

    bool IsDisactivated() { return !IsActive; }
private:
    bool IsActive = true;
    PhysicalComponent m_physics;
    GraphicsComponent m_graphics;
};

