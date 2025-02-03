#include "WeaponPowerPickup.h"
#include "IUpgradableShip.h"
#include "AnimationComponent.h"

WeaponPowerPickup::WeaponPowerPickup()
{
	setup("png/PUMissil.png", 4, 2, 25);
}

void WeaponPowerPickup::start()
{
	animation_component_->play_animation(0, 0, 2, 4,true);
}

void WeaponPowerPickup::call_pickup(class IUpgradableShip* other)
{
	if (other) {
		other->upgrade_weapon();
	}
}
