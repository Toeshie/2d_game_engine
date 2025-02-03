#include "Player.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "PlayerBullet.h"
#include "HealthComponent.h"
#include "Explosion.h"
#include "TimerManager.h"
#include "Companion.h"
#include "MathHelper.h"
#include "HeavyBullet.h"
#include "MediumBullet.h"
#include "GameEngine.h"
#include "AudioComponent.h"
#include "AudioManager.h"

Player::Player()
{
	add_tag("Player");

	// initialize components
	sprite_component_ = add_component<Sprite>("png/Ship1.png", 7, 1, 1.f, 1);
	animation_component_ = add_component<animation_component>(sprite_component_, false, 8.f);
	physics_component_ = add_component<PhysicsComponent>(BodyType::dynamic, 0, 1, 1);
	collider_ = add_component<CircleCollision>(physics_component_, 20);
	health_component_ = add_component<HealthComponent>(100);

	// Setup health callbacks
	health_component_->on_die.Add(this, &Player::on_zero_health);
	health_component_->on_respawn.Add(this, &Player::on_revive);

	// Setup shooting sound
	audio_component_ = add_component<AudioComponent>();
	audio_component_->set_sound("player_shoot");

	// initialize companion positions
	available_positions_ = companion_positions_;
}

void Player::handle_events()
{
	input_component::handle_events();

	if (!health_component_->get_is_alive()) return;

	is_shooting_ = Input::is_fire_key_down();
	if (is_shooting_ && shots_timer_ >= fire_rate_)
	{
		BaseBulletClass* bullet = nullptr;
		switch (weapon_level_) {
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
			bullet->get_physics_component()->set_position(
				calculate_fire_position(bullet_position_multiplier_)
			);
			bullet_position_multiplier_ *= -1;
		}

		shots_timer_ = 0.f;
		audio_component_->play();
	}
}

void Player::update(float delta_time)
{
	shots_timer_ += delta_time;
	move(delta_time);
	change_animation();
	input_component::update(delta_time);
}

void Player::move(float delta_time)
{
	// Calculate velocity based on input
	Vector2D velocity;
	velocity.x = input_right_axis_ * move_speed_;
	velocity.y = -input_up_axis_ * move_speed_;
	physics_component_->set_velocity(velocity);

	// Screen boundaries
	const float SCREEN_WIDTH = 500.0f;
	const float SCREEN_HEIGHT = 740.0f;
	const float PLAYER_RADIUS = 5.0f;

	// Get and clamp position
	Vector2D current_pos = transform.get_position();
	float clamped_x = MathHelper::clamp_float(current_pos.x, PLAYER_RADIUS, SCREEN_WIDTH - PLAYER_RADIUS);
	float clamped_y = MathHelper::clamp_float(current_pos.y, PLAYER_RADIUS, SCREEN_HEIGHT - PLAYER_RADIUS);

	// Update position if needed
	if (current_pos.x != clamped_x || current_pos.y != clamped_y) {
		physics_component_->set_position(Vector2D(clamped_x, clamped_y));
	}
}

void Player::change_animation()
{
	if (input_right_axis_ > 0.f)
	{
		if (!animation_component_->is_playing_animation(0, 4, 0, 6)) 
			animation_component_->play_animation(0, 4, 0, 6, false);
	}
	else if (input_right_axis_ < 0.f)
	{
		if (!animation_component_->is_playing_animation(0, 0, 0, 2)) 
			animation_component_->play_animation(0, 0, 0, 2, false);
	}
	else
	{
		if (!animation_component_->is_playing_animation(0, 3, 0, 3)) 
			animation_component_->play_animation(0, 3, 0, 3, true);
	}
}

Vector2D& Player::calculate_fire_position(int position_multiplier)
{
	const float FRONT_OFFSET_X = 16.0f;
	const float FRONT_OFFSET_Y = -50.0f;
	fire_position_ = transform.get_position() + Vector2D(FRONT_OFFSET_X, FRONT_OFFSET_Y);
	return fire_position_;
}

void Player::on_zero_health()
{
	game_world::instantiate_object<Explosion>()->transform.set_position(transform.get_position());
	sprite_component_->set_active(false);
	collider_->set_collision_enabled(false);
	remove_tag("Player");
}

void Player::on_revive()
{
	add_tag("Player");
	collider_->set_collision_enabled(true);
	sprite_component_->set_active(true);
}

void Player::upgrade_shields(int amount_to_heal)
{
	health_component_->heal(amount_to_heal);
}

void Player::upgrade_weapon()
{
	weapon_level_ = MathHelper::clamp_int(weapon_level_ + 1, 1, 3);
}

void Player::add_companion()
{
	if (available_positions_.empty()) {
		return;
	}

	Vector2D pos = available_positions_[0];
	Companion* companion = game_world::instantiate_object<Companion>(pos);
	companion->on_companion_die.Add(this, &Player::on_companion_die);
	companion->set_target(this, pos);
	available_positions_.erase(available_positions_.begin());
}

void Player::on_companion_die(Companion* companion)
{
	if (!companion) return;
	available_positions_.push_back(companion->GetPositionTarget());
}

void Player::on_became_visible()
{
	
}

void Player::on_became_hidden()
{
	
}

