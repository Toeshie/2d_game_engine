#pragma once
#include "Enemy.h"

class Rusher : public Enemy
{
public:
	Rusher();

	Vector2D moving_direction = Vector2D::down(); 

	virtual void update(float deltaTime) override;
};

