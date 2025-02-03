#include "BasePickupClass.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "IUpgradableShip.h"
#include "GameWorld.h"
#include "AudioComponent.h"
#include "AudioManager.h"

BasePickupClass::BasePickupClass()
{
	add_tag("Pickup");
	
	// Setup pickup sound
	audio_component_ = add_component<AudioComponent>();
	audio_component_->set_sound("powerup_collect");
}

void BasePickupClass::setup(const char* spritePath, int spriteColumns, int spriteRows, int colliderRadius)
{
	sprite_component_ = add_component<Sprite>(spritePath, spriteColumns,
		spriteRows, 1.0f, 1);
	animation_component_ = add_component<animation_component>(sprite_component_, true, 8.0f);
	physics_component_ = add_component<PhysicsComponent>(BodyType::kinematic, 0, 1, 1);
	collider_ = add_component<CircleCollision>(physics_component_, colliderRadius);
	collider_->set_is_trigger(true);
	collider_->on_trigger_enter.Add(this, &BasePickupClass::on_trigger_enter);
}

void BasePickupClass::update(float deltaTime)
{
	physics_component_->set_velocity(Vector2D::down() * 30.0f);
}

void BasePickupClass::on_trigger_enter(game_object* other)
{
	IUpgradableShip* otherUpgradableShip = dynamic_cast<IUpgradableShip*>(other);
	if (otherUpgradableShip != nullptr)
	{
		// Play sound when collecting power-up
		audio_component_->play();
		call_pickup(otherUpgradableShip);
		game_world::destroy_object(this);
	}
}

void BasePickupClass::on_became_hidden()
{
	if (was_visible_) {
		game_world::destroy_object(this);
	}
}

void BasePickupClass::on_became_visible()
{
	was_visible_ = true;
}
