#include "Explosion.h"
#include "Sprite.h"
#include "AnimationComponent.h"
#include "GameWorld.h"
#include "AudioComponent.h"
#include "AudioManager.h"

Explosion::Explosion()
{
	initialize();
}

Explosion::Explosion(Transform* transform)
{
	if (transform)
	{
		get_transform()->set_position(transform->get_position());
	}
	initialize();
}

void Explosion::initialize()
{
	// Setup explosion sound
	audio_component_ = add_component<AudioComponent>();
	audio_component_->set_sound("explosion_sound");

	sprite_component_ = add_component<Sprite>("png/explode64.png", 5, 2, 1.f, 0);
	animation_component_ = add_component<animation_component>(sprite_component_, true, 12.f);
	animation_component_->set_animation_looping(false);
	animation_component_->on_animation_ended.Add(this, &Explosion::on_animation_end);
	
	// Play explosion sound when created
	audio_component_->play();
}

void Explosion::on_animation_end()
{
	game_world::destroy_object(this);
}


