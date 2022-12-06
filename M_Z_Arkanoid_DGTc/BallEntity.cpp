#include "BallEntity.h"
#include "Window.h"
#include "GameWorld.h"

#define MaxBallSpeed (float)0.45

#define BallBaseWidthAndHeight 30

void BallEntity::update(GameWorld* gameworld, double ts)
{
	if (IsActive)
	{
		m_graphics.update(this, gameworld, ts);
		m_physics.update(this, gameworld, ts);
	}
}

void BallEntity::draw()
{
	if(IsActive)
		m_graphics.draw(this);
}

bool BallEntity::init(GameWorld* gameworld)
{

	int width = BallBaseWidthAndHeight * gameworld->GetWorldUnits().x_;
	int height = BallBaseWidthAndHeight * gameworld->GetWorldUnits().y_;

	SetTextureSize(width, height);

	if (!m_graphics.init(gameworld->GetTextureManager(), this, BallTexturePath))
		return false;
	return true;
}

bool BallEntity::IsLoosed(GameWorld* gameworld)
{
	if(IsActive)
		return GetCoord().y_ > gameworld->GetBorders().y_ * 0.97;
	return false;
}

void BallEntity::spawn(Scope(PlayerEntity) player, GameWorld* gameworld)
{
	SetX(player->GetBallSpawnPoint().x_- this->GetCoord().width_ / 2);
	SetY(player->GetBallSpawnPoint().y_- this->GetCoord().height_ / 2);

	float Ax = gameworld->GetCursorXY().x_ - GetOrigin().x_;
	float Ay = gameworld->GetCursorXY().y_ - GetOrigin().y_;

	float Nax = Ax;
	float Nay = Ay;

	if (Nax < 0)
		Nax *= -1;
	if (Nay < 0)
		Nay *= -1;

	m_physics.init(this, (Ax / (Nax + Nay) * MaxBallSpeed), (Ay / (Nay + Nax) * MaxBallSpeed));

	IsActive = true;
}
