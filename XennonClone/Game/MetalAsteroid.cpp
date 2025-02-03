#include "MetalAsteroid.h"
#include <ctime>
#include "GameWorld.h"
#include "PhysicsComponent.h"

MetalAsteroid::MetalAsteroid()
{
	// Initialize random seed
	srand(time(nullptr));
	int metalAsteroidType = rand() % 3;

	// Set enemy data based on asteroid type
	switch (metalAsteroidType)
	{
	case 0:  // Small asteroid
		enemy_data_ = EnemyData(
			"Enemy",            // tag
			"png/MAster32.png", // sprite path
			8,                  // columns
			2,                  // rows
			1.f,               // scale
			15,                // health
			999,               // damage
			15,                // score
			30,                // speed
			0                  // detection range
		);
		break;
	case 1:  // Medium asteroid
		enemy_data_ = EnemyData(
			"Enemy",            // tag
			"png/MAster64.png", // sprite path
			8,                  // columns
			3,                  // rows
			1.f,               // scale
			25,                // health
			999,               // damage
			30,                // score
			30,                // speed
			0                  // detection range
		);
		break;
	case 2:  // Large asteroid
		enemy_data_ = EnemyData(
			"Enemy",            // tag
			"png/MAster96.png", // sprite path
			5,                  // columns
			5,                  // rows
			1.f,               // scale
			60,                // health
			999,               // damage
			40,                // score
			30,                // speed
			0                  // detection range
		);
		break;
	}
	setup();
}

void MetalAsteroid::update(float deltaTime)
{
	physics_component_->set_velocity(movement_direction_ * enemy_data_.speed);
}

void MetalAsteroid::on_became_hidden()
{
	game_world::destroy_object(this);
}

