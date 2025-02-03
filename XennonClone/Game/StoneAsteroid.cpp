#include "StoneAsteroid.h"
#include <ctime>
#include "PhysicsComponent.h"
#include "GameWorld.h"

StoneAsteroid::StoneAsteroid()
{
	srand(time(nullptr));
	asteroid_type_ = static_cast<AsteroidType>(rand() % 3);
	asteroid_data();
}

StoneAsteroid::StoneAsteroid(AsteroidType asteroidType)
{
	asteroid_type_ = asteroidType;
	asteroid_data();
}

void StoneAsteroid::asteroid_data()
{
	switch (asteroid_type_)
	{
	case AsteroidType::Small:
		enemy_data_ = EnemyData(
			"Enemy",            // tag
			"png/SAster32.png", // sprite path
			8,                  // columns
			2,                  // rows
			1.f,               // scale
			15,                // health
			15,                // damage
			15,                // score
			40,                // speed
			65                 // detection range
		);
		break;
	case AsteroidType::Medium:
		enemy_data_ = EnemyData(
			"Enemy",            // tag
			"png/SAster64.png", // sprite path
			8,                  // columns
			3,                  // rows
			1.f,               // scale
			25,                // health
			15,                // damage
			30,                // score
			35,                // speed
			35                 // detection range
		);
		break;
	case AsteroidType::Large:
		enemy_data_ = EnemyData(
			"Enemy",            // tag
			"png/SAster96.png", // sprite path
			5,                  // columns
			5,                  // rows
			1.f,               // scale
			100,                // health
			30,                // damage
			40,                // score
			25,                // speed
			15                 // detection range
		);
		break;
	}
	setup();
}

void StoneAsteroid::on_became_hidden()
{
	game_world::destroy_object(this);
}

void StoneAsteroid::update(float deltaTime)
{
	physics_component_->set_velocity(movement_direction * enemy_data_.speed);
}

void StoneAsteroid::on_destroyed()
{
	if (asteroid_type_ == AsteroidType::Large ||
		asteroid_type_ == AsteroidType::Medium)
	{
		float direction_multiplier = 0.5f;
		AsteroidType smaller_asteroid_type = static_cast<AsteroidType>(
			static_cast<int>(asteroid_type_) - 1
		);
		
		for (int i = 0; i < 2; ++i)
		{
			StoneAsteroid* smaller_asteroid = game_world::instantiate_object<StoneAsteroid>(smaller_asteroid_type);
			smaller_asteroid->get_component<PhysicsComponent>()->set_position(transform.get_position());
			smaller_asteroid->movement_direction = Vector2D(direction_multiplier, 0.5f);
			direction_multiplier *= -1;
		}
	}
	Enemy::on_destroyed();
}
