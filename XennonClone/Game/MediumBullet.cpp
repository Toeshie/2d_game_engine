#include "MediumBullet.h"
#include "AnimationComponent.h"

MediumBullet::MediumBullet()
{
	bullet_data_ = BulletData(
		"png/missile.png",  // sprite path
		3,                  // columns
		2,                  // rows
		20,                 // damage
		"Enemy",            // tag
		10,                 // speed
		2.f,               // scale
		250,               // lifetime
		Vector2D::up()     // direction
	);
	setup();
}

void MediumBullet::start()
{
	animation_component_->play_animation(1, 0, 1, 1, true);
}
