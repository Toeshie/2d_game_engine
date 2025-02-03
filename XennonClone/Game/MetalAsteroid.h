#pragma once
#include "Enemy.h"

class MetalAsteroid : public Enemy
{
public:
	MetalAsteroid();
	void update(float deltaTime) override;
	void on_became_hidden() override;

private:
	Vector2D movement_direction_ = Vector2D::down();

};

