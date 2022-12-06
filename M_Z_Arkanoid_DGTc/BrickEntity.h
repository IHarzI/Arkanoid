#pragma once


#include "BaseEntity.h"
#include "GraphicsComponent.h"

#define SimpleBrickTexturePath "Textures/BlueBrick.png"

#define SpecialBrickTexturePath "Textures/OrangeBrick.png"

#define BrickXCount 24
#define BrickYCount 10

class BrickEntity :
    public BaseEntity
{
public:
    BrickEntity(int id)
        : BaseEntity(Coord2D()), IDPos(id)
    {
        SetType(SIMPLE_BRICK);
    }

    virtual void update(GameWorld* gameworld, double ts) override;
    virtual void draw() override;
    virtual bool init(GameWorld* gameworld) override;

    void ChainReact(GameWorld* gameworld, BaseEntity* entity, int id);
    

    Pair(bool, BaseEntity*) isBrickCollided(GameWorld* gameworld, BaseEntity* entity);


    virtual bool IsEntityActive() override { return IsActive; }

    void Destroy(BaseEntity* entity, GameWorld* gameworld);
    void Respawn();

private:
    bool IsActive = true;
    int IDPos = 0;
    GraphicsComponent m_graphics;
  };

