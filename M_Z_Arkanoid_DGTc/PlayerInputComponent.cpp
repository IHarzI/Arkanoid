#include "PlayerInputComponent.h"

#include "Types.h"
#include "BaseEntity.h"
#include "Window.h"
#include "GameWorld.h"

#define MovementSpeedBase 0.5

void PlayerInputComponent::onKeyPressed(BaseEntity* player, GameWorld* gameworld, Key key)
{
	if (!player)
		return;
	// make a cast
	auto ActualPlayer = (PlayerEntity*)player;

	const float movementspeed_ = MovementSpeedBase * gameworld->GetWorldUnits().x_;

	switch (key)
	{
	case RIGHT_KEY:
		ActualPlayer->SetMoveXSpeed(movementspeed_);
		break;
	case LEFT_KEY:
		ActualPlayer->SetMoveXSpeed(-movementspeed_);
		break;
	default:
		break;
	}
}

void PlayerInputComponent::OnKeyReleased(BaseEntity* player, GameWorld* gameworld, Key key)
{
	
	auto ActualPlayer = (PlayerEntity*)player;
	ActualPlayer->SetMoveXSpeed(0);
	switch (key)
	{
	case RIGHT_KEY:
	case LEFT_KEY:
		ActualPlayer->SetMoveXSpeed(0);
		break;
	default:
		break;
	}
	
}

bool PlayerInputComponent::onMouseButtonClick(MouseButton button, bool isReleased)
{
	if(button == MOUSE_LEFT && isReleased)
		return true;
	return false;
}


void PlayerInputComponent::update(BaseEntity* player, GameWorld* gameworld, double ts)
{
}

