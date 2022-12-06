#pragma once

#include "Types.h"

class BaseEntity;

class Component
{
public:
	Component(){};
	virtual ~Component() {};

	virtual void update(BaseEntity* entity, GameWorld* gameworld, double ts) = 0;
};
