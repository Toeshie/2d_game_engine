#include "LonerBullet.h"
#include "GameWorld.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

LonerBullet::LonerBullet()
{
	bullet_data_ = BulletData(
		"png/enemybullet.png",  // sprite path
		1,                      // columns
		8,                      // rows
		25,                     // damage
		"Player",               // tag
		10,                     // speed
		2.f,                    // scale
		100,                    // lifetime
		Vector2D::down()        // direction
	);
	setup();
}

void LonerBullet::start()
{
	if (!animation_component_->is_playing_animation(0, 0, 0, 7))
	{
		animation_component_->play_animation(0, 0, 0, 7, true);
	}

	game_object* player = game_world::find_object_with_tag("Player");
	game_object* parent = game_world::find_object_with_tag("Loner");
	
	if (player && parent)
	{
		Vector2D my_pos = parent->get_transform()->get_position();
		Vector2D player_pos = player->get_transform()->get_position();
		bullet_data_.direction = (player_pos - my_pos).normalize();
	}
}
