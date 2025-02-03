#include "ShieldPickup.h"
#include "IUpgradableShip.h"
#include "AnimationComponent.h"

ShieldPickup::ShieldPickup()
{
	setup("png/PUShield.png", 4, 2, 25);
}

void ShieldPickup::start()
{
	animation_component_->play_animation(0, 0, 1, 3, true);
}

void ShieldPickup::call_pickup(class IUpgradableShip* other)
{
	if (other) {
		other->upgrade_shields(10);
	}
}

