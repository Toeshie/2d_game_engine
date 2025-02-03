#include "DronePack.h"
#include "GameWorld.h"
#include "Drone.h"
#include "PhysicsComponent.h"
#include "EnemyManager.h"

void DronePack::update(float deltaTime)
{
	if (number_drones_to_spawn_ <= 0) { 
		game_world::destroy_object(this);
		return;
	}
	spawns_timer_ += deltaTime;
	if (spawns_timer_ >= time_between_spawns_)
	{
		Vector2D difference = Vector2D(0.0f, number_drones_to_spawn_ * 50.0f);
		Drone* drone = game_world::instantiate_object<Drone>();
		drone->get_component<PhysicsComponent>()->set_position(transform.get_position() - difference);
		number_drones_to_spawn_--;
		spawns_timer_ = 0.0f;
	}
}
