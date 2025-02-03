#pragma once
#include "GameObject.h"

class PowerUpManager : public game_object 
{
public:
	void update(float delta) override;

private:
	Vector2D get_random_position();
	void spawn_random_pickup();

	// Spawn configuration
	static constexpr float wait_time = 8.0f;
	Vector2D spawn_positions_[4] = {
		Vector2D(50, -10),
		Vector2D(300, -10),
		Vector2D(150, -10),
		Vector2D(200, -10)
	};
	
	float current_time_ = 0.0f;
	float wait_time_ = wait_time;
};

