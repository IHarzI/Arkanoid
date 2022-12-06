#include "PhysicalComponent.h"

#include "GameWorld.h"

void PhysicalComponent::init(BaseEntity* entity, float x, float y)
{
	velocity.x_ = x;
	velocity.y_ = y;
	fLocation.SetValue(entity->GetCoord().x_, entity->GetCoord().y_);
}

void PhysicalComponent::update(BaseEntity* entity, GameWorld* gameworld, double ts)
{
	if (!entity)
		return;

	if (entity->GetType() == BALL)
	{
		BallEntity* ball = ((BallEntity*)entity);
		if (!ball->GetIsActive())
			return;

		checkBorders(entity, gameworld, ts);

		auto ColWithPlayer = gameworld->IsColidedWithPlayer(entity);
		if (ColWithPlayer.first)
		{
			collisionResponse(entity, ColWithPlayer.second,true);
		}

		auto ColWithBrick = gameworld->IsColidedWithBricks(entity);

		if (ColWithBrick.first)
		{
			collisionResponse(entity, ColWithBrick.second);
		}

		calcFLoc(ts);

		ball->move((int)fLocation.x_, (int)fLocation.y_);

	}
	else if (entity->GetType() == NEGATIVE_ABILITY || entity->GetType() == POSITIVE_ABILITY)
	{
		AbilityEntity* ability = ((AbilityEntity*)entity);

		checkBorders(entity, gameworld, ts);

		auto ColWithPlayer = gameworld->IsColidedWithPlayer(entity);
		if (ColWithPlayer.first)
		{
			gameworld->AddAbilityToPlayer(entity);
			ability->Disactivate();
			return;
		}
		
		calcFLoc(ts);

		ability->move((int)fLocation.x_, (int)fLocation.y_);
	}

}

void PhysicalComponent::checkBorders(BaseEntity* entity, GameWorld* gameworld, double ts)
{
	int XBorder = gameworld->GetBorders().x_ - entity->GetTextureSize().x_;
	int YBorder = gameworld->GetBorders().y_ + entity->GetTextureSize().y_;
	if (fLocation.x_ > XBorder || fLocation.x_ < 0.f)
	{
		velocity.x_ *= -1;
	}
	if (fLocation.y_ > YBorder || fLocation.y_ < 0.f)
	{
		velocity.y_ *= -1;
	}
}

void PhysicalComponent::collisionResponse(BaseEntity* ball, BaseEntity* colider, bool IsPlayerCollided)
{

	int overlapLeft{ ball->GetRightBound().x_ - colider->GetLeftBound().x_};
	int overlapRight{ colider->GetRightBound().x_ - ball->GetLeftBound().x_ };
	int overlapTop{ ball->GetDownBound().y_ - colider->GetUpBound().y_};
	int overlapBottom{ colider->GetDownBound().y_ - ball->GetUpBound().y_};

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	int minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	int minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		velocity.x_ *= -1;
	else
	{
		// make additional possibility to control ball
		if (IsPlayerCollided)
		{
			velocity.x_ = (overlapLeft > overlapRight) ? abs(velocity.x_) : abs(velocity.x_) * -1;
		}
		
		velocity.y_ *= -1;
	}
	

}

void PhysicalComponent::calcFLoc(double ts)
{
		fLocation.x_ += velocity.x_ * ts;
		fLocation.y_ += velocity.y_ * ts;

}

