#include "GameWorld.h"

bool AbilitiCheck(Scope(AbilityEntity) ability) { return ability->IsDisactivated(); }

void GameWorld::update(double ts)
{
	if(ball_->GetIsActive())
		AbilitiTimeToSpawn -= (ts);

	player_->update(this, ts);

	if (ball_->GetIsActive())
		ball_->update(this, ts);

	for (auto abiliti = abilities_.begin(); abiliti != abilities_.end(); abiliti++)
		(*abiliti)->update(this, ts);

	if (AbilitiTimeToSpawn <= 0)
	{
		abilities_.push_back(CreateScope(AbilityEntity));
		abilities_.back()->init(this);
		AbilitiTimeToSpawn = ABILITIESTIMETOSPAWN;
	}

	if (ball_->IsLoosed(this))
	{
		restart();
		return;
	}

	abilities_.remove_if(AbilitiCheck);

}

void GameWorld::draw()
{
	for (int brickID = 0; brickID < BRICKCOUNT; brickID++)
	{
		if (bricks_[brickID]->IsEntityActive())
			bricks_[brickID]->draw();
	}
	player_->draw();
	for (auto abiliti = abilities_.begin(); abiliti != abilities_.end(); abiliti++)
		(*abiliti)->draw();
	ball_->draw();
}

bool GameWorld::init(TextureManager* texturemanager, Window* window)
{
	AbilitiTimeToSpawn = ABILITIESTIMETOSPAWN;
	srand(getTickCount());
	texturemanager_ = texturemanager;
	window_ = window;
	player_ = CreateScope(PlayerEntity);
	ball_ = CreateScope(BallEntity);

	for (int brickID = 0; brickID < BRICKCOUNT; brickID++)
	{
		bricks_[brickID] = CreateScope(BrickEntity, brickID);
	}

	if (!player_->init(this))
		return false;
	if(!ball_->init(this))
		return false;
	for (int i = 0; i < BRICKCOUNT; i++)
		if(!bricks_[i]->init(this))
			return false;
}

void GameWorld::restart()
{
	AbilitiTimeToSpawn = ABILITIESTIMETOSPAWN;
	player_->respawn(this);
	ball_->Destroy();
	for (int i = 0; i < BRICKCOUNT; i++)
		bricks_[i]->Respawn();
	abilities_.clear();
}

void GameWorld::onKeyPressed(Key k)
{
	
	if (k != Key::NONE_KEY)
		player_->onKeyPressed(this, k);
	
}

void GameWorld::onKeyReleased(Key k)
{
	player_->OnKeyReleased(this, k);
}


void GameWorld::onMouseButtonClick(MouseButton button, bool isReleased)
{
	if(!ball_->GetIsActive())
		if (player_->onMouseButtonClick(button, isReleased))
			ball_->spawn(player_, this);
}

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	player_.reset();
	ball_.reset();
	bricks_->reset();
	abilities_.clear();
}

Pair(bool, BaseEntity*) GameWorld::IsColidedWithBricks(BaseEntity* entity)
{
	for (int i = 0; i < BRICKCOUNT; i++)
	{
		if (bricks_[i]->IsEntityActive())
		{
			auto result = bricks_[i]->isBrickCollided(this, entity);
			if (result.first)
				return result;
		}
	}
	return MakePair(false,nullptr);
}
