#pragma once

#include "PlayerEntity.h"
#include "PhysicalComponent.h"
#include "GraphicsComponent.h"

#define BallTexturePath "Textures/Ball.png"

class BallEntity :
    protected BaseEntity
{
public:
    BallEntity()
        : BaseEntity(Coord2D(), BALL) {};

    virtual void update(GameWorld* gameworld, double ts) override;

    virtual void draw() override;

    virtual bool init(GameWorld* gameworld) override;

    const bool GetIsActive() { return IsActive; }

    bool IsLoosed(GameWorld* gameworld);

    void Destroy() { IsActive = false;}

    void move(int x = 0, int y = 0) { SetX(x); SetY(y); }

    void spawn(Scope(PlayerEntity) player, GameWorld* gameworld);
private:
    bool IsActive = false;
    PhysicalComponent m_physics;
    GraphicsComponent m_graphics;
};

