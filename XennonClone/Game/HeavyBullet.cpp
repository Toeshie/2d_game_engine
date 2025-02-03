#include "HeavyBullet.h"
#include "AnimationComponent.h"

HeavyBullet::HeavyBullet()
{
	bullet_data_ = BulletData(
		"png/missile.png",  // sprite path
		3,                  // columns
		2,                  // rows
		40,                 // damage
		"Enemy",            // tag
		10,                 // speed
		2.f,               // scale
		250,               // lifetime
		Vector2D::up()     // direction
	);
	setup();
}

void HeavyBullet::start()
{
	animation_component_->play_animation(2, 0, 2, 1, true);
}
