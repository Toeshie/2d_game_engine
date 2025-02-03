#include "Drone.h"
#include "PhysicsComponent.h"
#include <math.h> 
#include "GameWorld.h"

Drone::Drone()
{
	add_tag("Drone");
	sine_movement_data = SineMovementData(6.0f, 4.0f);
	enemy_data_ = EnemyData("Enemy", "png/drone.png", 8, 2, 1.0f, 25, 10, 25, 35, 50);
	setup();
}

void Drone::update(float deltaTime)
{
	sine_movement_data.ticks_counter += sine_movement_data.sine_speed * deltaTime;
	//will continuously return between -1 and 1
	move_direction.x = sine_movement_data.sine_amplitude * sin(sine_movement_data.ticks_counter);
	physics_component_->set_velocity(move_direction * enemy_data_.speed);
}

void Drone::on_became_visible()
{
	can_destroy = true;
}

void Drone::on_became_hidden()
{
	if (can_destroy) {
		game_world::destroy_object(this);
	}
}
