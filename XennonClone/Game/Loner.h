#pragma once
#include "Enemy.h"

class Loner : public Enemy
{
public:
	Loner();
	void update(float deltaTime) override;
	void on_became_visible() override;
	void on_became_hidden() override;

	Vector2D move_direction = Vector2D::left();

private:
	void shoot();

	bool can_shoot_ = false;
	float current_delay_ = 0.0f;
	float shoot_delay_ = 1.0f;
};

