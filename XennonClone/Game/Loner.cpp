#include "Loner.h"
#include "PhysicsComponent.h"
#include "GameWorld.h"
#include "LonerBullet.h"

Loner::Loner()
{
	enemy_data_ = EnemyData(
		"Enemy",           // tag
		"png/lonerA.png", // sprite path
		4,                // columns
		4,               // rows
		1.f,            // scale
		35,             // health
		10,             // damage
		50,             // score
		10,             // speed
		150            // detection range
	);
	setup();
	current_delay_ = shoot_delay_;
	add_tag("Loner");
}

void Loner::shoot()
{
	game_world::instantiate_object<LonerBullet>()->get_physics_component()->
		set_position(transform.get_position());
}

void Loner::update(float deltaTime)
{
	physics_component_->set_velocity(move_direction * enemy_data_.speed * 2.5f);

	if (can_shoot_) {
		current_delay_ -= deltaTime;
		if (current_delay_ <= 0) {
			shoot();
			current_delay_ = shoot_delay_;
		}
	}
}

void Loner::on_became_visible()
{
	can_shoot_ = true;
}

void Loner::on_became_hidden()
{
	if (can_shoot_) {
		Enemy::on_became_hidden();
	}
}
