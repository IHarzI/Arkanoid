#include "BrickEntity.h"
#include "GameWorld.h"

#define SPECIALBRICKCHANCE 7

#define GAP_X 4.8
#define GAP_Y 5

#define EXPLODERADIUSOFFSET 85

void BrickEntity::update(GameWorld* gameworld, double ts)
{
}

void BrickEntity::draw()
{
	if(IsActive)
	m_graphics.draw(this);
}

bool BrickEntity::init(GameWorld* gameworld)
{
	if ((int)rand() % SPECIALBRICKCHANCE == 1)
	{
		SetType(SPECIAL_BRICK);
	}

	const float GapX = GAP_X * gameworld->GetWorldUnits().x_;
	const float GapY = GAP_Y * gameworld->GetWorldUnits().y_;

	const int BrickBaseWidth = 75;
	const int BrickBaseHeight = 45;

	int width = BrickBaseWidth * gameworld->GetWorldUnits().x_;
	int height = BrickBaseHeight * gameworld->GetWorldUnits().y_;

	int XLevel = (int)(IDPos % BrickXCount);
	int YLevel = (int)(IDPos / BrickXCount);


	int BrickPositionX = (int)(XLevel * (GapX + width) + GapX);
	int BrickPositionY = (int)(YLevel * (GapY + height) + GapY);

	SetCoord(BrickPositionX, BrickPositionY, width, height);

	const char* path = SimpleBrickTexturePath;
	
	if (GetType() == SPECIAL_BRICK)
		path = SpecialBrickTexturePath;

	if (!m_graphics.init(gameworld->GetTextureManager(), this,path))
		return false;
	return true;
}

void BrickEntity::ChainReact(GameWorld* gameworld, BaseEntity* entity,int id)
{
	int2 ExplodeRadius(EXPLODERADIUSOFFSET * gameworld->GetWorldUnits().x_, EXPLODERADIUSOFFSET * gameworld->GetWorldUnits().y_);

	if(abs(this->GetOrigin().x_-entity->GetOrigin().x_)<= ExplodeRadius.x_ && abs(this->GetOrigin().y_ - entity->GetOrigin().y_) <= ExplodeRadius.y_)
		Destroy(this,gameworld);
	
}

Pair(bool, BaseEntity*) BrickEntity::isBrickCollided(GameWorld* gameworld, BaseEntity* entity)
{
	auto result = IsCollided(entity);
	if (result.first)
		Destroy(this,gameworld);
	return result;
}

void BrickEntity::Destroy(BaseEntity* entity, GameWorld* gameworld)
{
	if (IsActive)
	{
		IsActive = false;
		if (GetType() == SPECIAL_BRICK)
			gameworld->BrickChainReaction(this, IDPos);
	}
}

void BrickEntity::Respawn()
{
	SetType(SIMPLE_BRICK);
	if ((int)rand() % SPECIALBRICKCHANCE == 1)
	{
		SetType(SPECIAL_BRICK);
	}

	IsActive = true;
}
