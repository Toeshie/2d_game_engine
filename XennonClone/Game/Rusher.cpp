#include "Rusher.h"
#include "PhysicsComponent.h"

Rusher::Rusher()
{
	enemy_data_ = EnemyData(
		"Enemy",            // tag
		"png/rusher.png",  // sprite path
		4,                 // columns
		6,                // rows
		1.f,             // scale
		30,              // health
		10,              // damage
		50,              // score
		40,              // speed
		100              // detection range
	);
	setup();
}

void Rusher::update(float deltaTime)
{
	physics_component_->set_velocity(moving_direction * enemy_data_.speed * 2.0f);
}
