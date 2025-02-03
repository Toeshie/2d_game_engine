#include "PlayerBullet.h"
#include "AnimationComponent.h"

PlayerBullet::PlayerBullet()
{
	bullet_data_ = BulletData(
		"png/missile.png",  // sprite path
		4,                  // columns
		2,                  // rows
		20,                 // damage
		"Enemy",            // tag
		10,                 // speed
		2.f,               // scale
		800,               // lifetime
		Vector2D::up()     // direction
	);
	setup();
}

void PlayerBullet::start()
{
	if (!animation_component_->is_playing_animation(0, 0, 0, 1)) 
	{
		animation_component_->play_animation(0, 0, 0, 1, true);
	}

	game_object::start();
}

