#pragma once
#include "Component.h"

class PlayerInputComponent :
    public Component
{
public:
    PlayerInputComponent(){}
    ~PlayerInputComponent() {}
    void onKeyPressed(BaseEntity* player, GameWorld* gameworld, Key key);
    void OnKeyReleased(BaseEntity* player, GameWorld* gameworld, Key key);
   
    bool onMouseButtonClick(MouseButton button, bool isReleased);

    virtual void update(BaseEntity* player, GameWorld* gameworld, double ts) override;
};

