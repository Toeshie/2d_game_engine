#include "ParallaxComponent.h"
#include "Sprite.h"
#include "GameObject.h"

void parallax_component::start()
{
	sprite_component_ = component_owner_->get_component<Sprite>();
	
	if (sprite_component_ != nullptr) {
		component_owner_->transform.set_position(0.f, -300.f);
	}
}

void parallax_component::update(float deltaTime)
{	
	if (!sprite_component_) return;

	const float reset_y = -300.f;
	const float max_y = sprite_component_->sheet_height_ + 475.f;
	
	if (component_owner_->transform.get_position().y >= max_y) {
		component_owner_->transform.set_position(0.f, reset_y);
	} else {
		component_owner_->transform.add_position(Vector2D(0.f, speed_ * deltaTime));
	}
}

void parallax_component::on_destroyed()
{
	// Clean up if needed
	sprite_component_ = nullptr;
}
