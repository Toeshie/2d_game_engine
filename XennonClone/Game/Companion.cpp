#include "Companion.h"
#include "Player.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "PlayerBullet.h"
#include "MediumBullet.h"
#include "HeavyBullet.h"
#include "MathHelper.h"
#include "Explosion.h"


void Companion::start()
{
	animation_component_->play_animation(0, 0, 3, 3, true);
	animation_component_->set_animation_speed(3.0f);
}

Companion::Companion(Vector2D position)
{
	add_tag("Player");

	get_transform()->set_position(position);

	follow_target_ = nullptr;

	sprite_component_ = add_component<Sprite>("png/clone.png",4,5,1.0f,1);
	animation_component_ = add_component<animation_component>(sprite_component_,true,1.0f);

	health_component_ = add_component<HealthComponent>(100);
	health_component_->on_die.Add(this, &Companion::on_zero_health);

	phys_component_ = add_component<PhysicsComponent>(BodyType::dynamic, 0, 1, 1);
	collider_component_ = add_component<CircleCollision>(phys_component_, 10);
	bullet_position_ = Vector2D(3.0f, 0.0f);
}

void Companion::set_target(Player* newTarget, Vector2D localPosition)
{
	if (newTarget) {
		follow_target_ = newTarget;
		follow_target_->get_health_component()->on_die.Add(this, &Companion::on_player_die);
		player_off_set_ = localPosition;
	}
}

void Companion::update(float delta)
{
	shots_timer_ += delta;
	if (follow_target_) {
		if (follow_target_->is_shooting() && shots_timer_ >= fire_rate_)
		{
			BaseBulletClass* bullet = nullptr;
			
			switch (weapon_power_)
			{
			case 2:
				bullet = game_world::instantiate_object<MediumBullet>();
				break;
			case 3:
				bullet = game_world::instantiate_object<HeavyBullet>();
				break;
			default:
			case 1:
				bullet = game_world::instantiate_object<PlayerBullet>();
				break;
			}
			if (bullet) {
				bullet->get_physics_component()->set_position(get_transform()->get_position() + bullet_position_);
				shots_timer_ = 0.0f;
			}
		}
		phys_component_->set_position(follow_target_->get_transform()->get_position() + player_off_set_);
	}
}

void Companion::on_zero_health()
{
	game_world::instantiate_object<Explosion>(get_transform());
	on_companion_die.Broadcast(this);
	game_world::destroy_object(this);
}

void Companion::on_player_die()
{
	game_world::destroy_object(this);
}

void Companion::upgrade_shields(int amountToHeal)
{
	health_component_->heal(amountToHeal);
}

void Companion::upgrade_weapon()
{
	weapon_power_ += 1;
	weapon_power_ = MathHelper::clamp_int(weapon_power_, 1, 3);
}
