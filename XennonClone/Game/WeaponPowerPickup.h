#pragma once
#include "BasePickupClass.h"

class WeaponPowerPickup : public BasePickupClass
{
public:
	WeaponPowerPickup();

	void start() override;

protected:
	void call_pickup(class IUpgradableShip* other) override;
};

