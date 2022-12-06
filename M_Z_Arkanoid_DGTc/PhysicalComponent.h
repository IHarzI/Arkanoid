#pragma once

#include "Component.h"

class PhysicalComponent : public Component
{

public:
	PhysicalComponent() {};
	~PhysicalComponent(){};

	vec2 GetVelocity() { return velocity; }

	void init(BaseEntity* entity, float x = 0, float y = 0);

	void SetVelocity(vec2 vel) { velocity = vel; }

	virtual void update(BaseEntity* entity, GameWorld* gameworld, double ts) override;
private:

	void checkBorders(BaseEntity* entity, GameWorld* gameworld, double ts);

	void collisionResponse(BaseEntity* ball, BaseEntity* colider, bool IsPlayerCollided = false);

	void calcFLoc(double ts);

	vec2 velocity;
	vec2 fLocation;
};


