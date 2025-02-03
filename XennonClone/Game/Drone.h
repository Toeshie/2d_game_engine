#pragma once
#include "Enemy.h"

struct SineMovementData
{
	float ticks_counter = 0.0f;
	float sine_speed = 5.0f;
	float sine_amplitude = 1.0f;

	SineMovementData() = default;
	SineMovementData(float speed, float amplitude) 
		: sine_speed(speed)
		, sine_amplitude(amplitude) 
	{}
};

class Drone : public Enemy
{
public:
	Drone();

	Vector2D move_direction = Vector2D(0.1f, 1.0f);

	SineMovementData sine_movement_data;

	bool can_destroy = false;

	void update(float deltaTime) override;
	void on_became_visible() override;
	void on_became_hidden() override;

};

