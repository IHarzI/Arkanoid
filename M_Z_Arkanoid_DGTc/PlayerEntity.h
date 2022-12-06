#pragma once

#include "BaseEntity.h"
#include "GraphicsComponent.h"
#include "AbilitysHandlerComponent.h"
#include "PlayerInputComponent.h"

#define PlayerTexturePath "Textures/Platform.png"

#define BallSpawnOffset (int)16

class PlayerEntity :
    protected BaseEntity
{
public:

    PlayerEntity()
        : BaseEntity(Coord2D(), PLAYER)
    {
        const int PlayerBaseWidth = 90;
        const int PlayerBaseHeight = 35;

        BaseTextureSize.x_ = PlayerBaseWidth;
        BaseTextureSize.y_ = PlayerBaseHeight;
    };

    virtual void update(GameWorld* gameworld, double ts) override;
    virtual void draw() override;
    virtual bool init(GameWorld* gameworld) override;

    void updateAbilitiModifier(float mod) { AbilityModifier = mod; SetTextureSize(BaseTextureSize.x_ * AbilityModifier, BaseTextureSize.y_ * AbilityModifier); updateScale(); }

    Pair(bool, BaseEntity*) isPlayerCollided(BaseEntity* entity) { return IsCollided(entity); }

    void onKeyPressed(GameWorld* gameworld, Key key) { m_inputcontroller.onKeyPressed(this,gameworld, key); }
    bool onMouseButtonClick(MouseButton button, bool isReleased) { return m_inputcontroller.onMouseButtonClick(button, isReleased);}

    void OnKeyReleased(GameWorld* gameworld, Key key) { m_inputcontroller.OnKeyReleased(this, gameworld, key); }

    int2 GetBallSpawnPoint() { return int2(GetCoord().x_ + GetCoord().width_ / 2, GetCoord().y_ - BallSpawnOffset); }

    void respawn(GameWorld* gameworld);

    AbilitysHandlerComponent* GetAbilityHandler() { return &m_abilityhandler; };

    void Move(GameWorld* gameworld, double ts);

    void SetMoveXSpeed(float x);

private:

    void updateScale() { m_graphics.UpdateTextureSize(this); }

    void FlyingEffect(GameWorld* gameworld, double ts);

    float AbilityModifier = 1;
    float FlyingModifier = 1;

    float FlyingPosition = 0;
    float MoveXSpeed = 0;

    int2 BaseTextureSize;
    PlayerInputComponent m_inputcontroller;
    AbilitysHandlerComponent m_abilityhandler;
    GraphicsComponent m_graphics;
};

