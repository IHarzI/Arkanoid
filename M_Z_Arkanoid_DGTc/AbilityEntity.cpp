#include "AbilityEntity.h"

#include "Window.h"
#include "GameWorld.h"

#define POSITIVEABILITYCHANCE 3
#define AbilityMaxSpeed 0.6

void AbilityEntity::update(GameWorld* gameworld, double ts)
{
	if (!IsActive)
		return;
	m_physics.update(this,gameworld, ts);
	m_graphics.update(this,gameworld, ts);

}

void AbilityEntity::draw()
{
	if (!IsActive)
		return;
	m_graphics.draw(this);
}

bool AbilityEntity::init(GameWorld* gameworld)
{
	srand(gameworld->GetTime());

	if (rand() % POSITIVEABILITYCHANCE == 0)
	{
		SetType(POSITIVE_ABILITY);
	}

	const int AbilityBaseWidthAndHeight = 30;

	const int RandomMod = 10;

	const float AbilitySpeedMod = AbilityMaxSpeed/ RandomMod;

	int width = AbilityBaseWidthAndHeight * gameworld->GetWorldUnits().x_;
	int height = AbilityBaseWidthAndHeight * gameworld->GetWorldUnits().y_;
	int StartPosX = (int)(gameworld->GetBorders().x_ / 2 - width / 2);
	int StartPosY = (int)(gameworld->GetBorders().y_ / 2 - height / 2);

	SetCoord(StartPosX, StartPosY, width, height);

	const char* path = NegativeAbilityTexturePath;
	if(GetType() == POSITIVE_ABILITY)
		path = PositiveAbilityTexturePath;

	if (!m_graphics.init(gameworld->GetTextureManager(), this, path))
		return false;

	float xvel = rand() % (RandomMod-2) * AbilitySpeedMod + AbilitySpeedMod;

	if (rand() % 2 == 0)
		xvel *= -1;

	float yvel = AbilityMaxSpeed - xvel;

	srand(gameworld->GetTime());

	if (rand() % 2 == 0)
		yvel *= -1;

	m_physics.init(this, xvel, yvel);
	return true;
}
