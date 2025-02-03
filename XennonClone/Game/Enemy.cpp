#include "Enemy.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "HealthComponent.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "ScorePopUpText.h"
#include "EnemyManager.h"
#include "Explosion.h"
#include <cmath>
#include "XennonGameWorld.h"

void Enemy::setup() 
{
	add_tag(enemy_data_.tag);

	sprite_component_ = add_component<Sprite>(enemy_data_.texture_path, enemy_data_.sprite_columns, 
		enemy_data_.sprite_rows, enemy_data_.scale, 1);
	animation_component_ = add_component<animation_component>(sprite_component_, true, 8.0f);
	physics_component_ = add_component<PhysicsComponent>(BodyType::kinematic, 0, 1, 1);
	collider_ = add_component<CircleCollision>(physics_component_, enemy_data_.collider_radius);

	health_component_ = add_component<HealthComponent>(enemy_data_.max_health);
	health_component_->on_die.Add(this, &Enemy::on_zero_health);
	collider_->set_is_trigger(true);
	collider_->on_trigger_enter.Add(this, &Enemy::on_trigger_enter);
}


void Enemy::on_destroyed()
{
	if (EnemyManager::get_instance() != nullptr) {
		EnemyManager::get_instance()->delete_enemy(this);
	}
}

void Enemy::on_zero_health()
{
	game_world::instantiate_object<Explosion>()->get_transform()->set_position(transform.get_position());

	XennonGameWorld* world = dynamic_cast<XennonGameWorld*>(game_world::get_world());
	if (world) {

		world->add_score(enemy_data_.score); // Change 'score_' to 'enemy_data_.score'
		game_world::instantiate_object<ScorePopUpText>(std::to_string(enemy_data_.score), 2.0f, transform.get_position());
	
	}
	game_world::destroy_object(this);
}

void Enemy::on_trigger_enter(game_object* other)
{
	if (other->has_tag("Player"))
	{
		HealthComponent* player_health_comp = other->get_component<HealthComponent>();
		if (player_health_comp) {
			player_health_comp->take_damage(enemy_data_.enemy_damage);
		}
		health_component_->take_damage(20);
	}
}

void Enemy::on_became_hidden()
{
	if (EnemyManager::get_instance() != nullptr) {
		EnemyManager::get_instance()->delete_enemy(this);
	}
}
