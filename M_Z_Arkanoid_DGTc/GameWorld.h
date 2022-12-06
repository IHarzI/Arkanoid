#pragma once

#include "BallEntity.h"
#include "BrickEntity.h"
#include "AbilityEntity.h"
#include "PlayerEntity.h"
#include "Window.h"

#define ABILITIESTIMETOSPAWN 20000
#define BRICKCOUNT BrickXCount * BrickYCount

class GameWorld
{
public:

	void update(double ts);

	void draw();

	bool init(TextureManager* texturemanager, Window* window);

	void restart();

	void onKeyPressed(Key k);
	void onKeyReleased(Key k);
	void onMouseButtonClick(MouseButton button, bool isReleased);

	GameWorld();
	~GameWorld();

	const unsigned int& GetTime() { return getTickCount(); };

	const int2& GetBorders() { return window_->GetXYBorders(); }
	const vec2& GetWorldUnits() { return window_->GetScreenUnits(); }

	TextureManager* GetTextureManager() { return texturemanager_; }

	const int2& GetCursorXY() { return int2(window_->GetMouseX(), window_->GetMouseY()); }

	Pair(bool, BaseEntity*) IsColidedWithPlayer(BaseEntity* entity) { return player_->isPlayerCollided(entity); }

	Pair(bool, BaseEntity*) IsColidedWithBricks(BaseEntity* entity);

	void BrickChainReaction(BaseEntity* entity, int id)
	{
		for (int brickID = 0; brickID < BRICKCOUNT; brickID++)
		{
			if(id!=brickID && bricks_[brickID]->IsEntityActive())
				bricks_[brickID]->ChainReact(this, entity, id);
		}
	}

	void AddAbilityToPlayer(BaseEntity* ability) { player_->GetAbilityHandler()->AddAbility(ability->GetType()); }

private:

	double AbilitiTimeToSpawn;
	Window* window_;
	TextureManager* texturemanager_;
	Scope(PlayerEntity) player_;
	Scope(BallEntity) ball_;
	Scope(BrickEntity) bricks_ [BRICKCOUNT];
	List(Scope(AbilityEntity)) abilities_;
};

