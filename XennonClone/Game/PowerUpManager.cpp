#include "PowerUpManager.h"
#include "CompanionPickup.h"
#include "ShieldPickup.h"
#include "WeaponPowerPickup.h"
#include "MathHelper.h"
#include "GameWorld.h"
#include "PhysicsComponent.h"

void PowerUpManager::update(float delta)
{
	current_time_ += delta;
	if (current_time_ >= wait_time_) {
		current_time_ = 0;
		spawn_random_pickup();
	}
}

Vector2D PowerUpManager::get_random_position()
{
	int pos = MathHelper::random_int_in_range(0, 3);
	return spawn_positions_[pos];
}

void PowerUpManager::spawn_random_pickup()
{
	BasePickupClass* pickup = nullptr;
	int rnd = MathHelper::random_int_in_range(0, 3);
	
	switch (rnd)
	{
	case 0:
		pickup = game_world::instantiate_object<WeaponPowerPickup>();
		break;
	case 2:
		pickup = game_world::instantiate_object<CompanionPickup>();
		break;
	default:
	case 1:
		pickup = game_world::instantiate_object<ShieldPickup>();
		break;
	}

	if (pickup) {
		PhysicsComponent* physics = pickup->get_component<PhysicsComponent>();
		if (physics) {
			physics->set_position(get_random_position());
		}
	}
}
