#include "PlayerEntity.h"
#include "GameWorld.h"

#define PlayerSpawnPointX (int)(gameworld->GetBorders().x_ / 2 - GetCoord().width_ / 2)
#define PlayerSpawnPointY (int)(gameworld->GetBorders().y_ * 0.9 - GetCoord().height_ / 2)

void PlayerEntity::update(GameWorld* gameworld, double ts)
{
	FlyingEffect(gameworld, ts);	

	Move(gameworld, ts);

	m_graphics.update(this,gameworld, ts);
	m_abilityhandler.update(this, gameworld, ts);

}

void PlayerEntity::draw()
{
	m_graphics.draw(this);
}

bool PlayerEntity::init(GameWorld* gameworld)
{

	float width = BaseTextureSize.x_ * gameworld->GetWorldUnits().x_;
	float height = BaseTextureSize.y_ * gameworld->GetWorldUnits().y_;
	float StartPosX = gameworld->GetBorders().x_ / 2 - width / 2;
	float StartPosY = gameworld->GetBorders().y_ * 0.9 - height / 2;

	FlyingPosition = PlayerSpawnPointY;
	MoveXSpeed = 0;
	SetCoord(PlayerSpawnPointX, PlayerSpawnPointY, (int)width, (int)height);

	if (!m_graphics.init(gameworld->GetTextureManager(), this, PlayerTexturePath))
		return false;
	return true;
}

void PlayerEntity::respawn(GameWorld* gameworld)
{
	updateAbilitiModifier(1);
	MoveXSpeed = 0;
	SetX(PlayerSpawnPointX);
	SetY(PlayerSpawnPointY);
	m_abilityhandler.clear();
}

void PlayerEntity::Move(GameWorld* gameworld, double ts)
{
	const int borderX = gameworld->GetBorders().x_ - GetTextureSize().x_;
	
	int NextPos = GetCoord().x_ + (int)(MoveXSpeed * ts);

	if (NextPos > borderX)
		NextPos = borderX;
	else if (NextPos < 0)
		NextPos = 0;
	SetX(NextPos);
	
}

void PlayerEntity::SetMoveXSpeed(float x)
{
	MoveXSpeed = x;
}

void PlayerEntity::FlyingEffect(GameWorld* gameworld, double ts)
{
		const float FloatingSpeed = 0.06 * gameworld->GetWorldUnits().y_ * FlyingModifier * ts;

		const float FlyingMaxOffset = gameworld->GetBorders().y_ * 0.9;
		const float FlyingMinOffset = gameworld->GetBorders().y_ * 0.85;


		FlyingPosition += FloatingSpeed;

		if (FlyingPosition < FlyingMinOffset)
		{
			FlyingModifier *= -1;
			FlyingPosition = FlyingMinOffset;
		}
		else if (FlyingPosition > FlyingMaxOffset)
		{
			FlyingModifier *= -1;
			FlyingPosition = FlyingMaxOffset;
		}
		SetY((int)FlyingPosition);
	
}
	

