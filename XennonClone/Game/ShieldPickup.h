#pragma once
#include "BasePickupClass.h"

class ShieldPickup : public BasePickupClass
{
public:
	ShieldPickup();

	void start() override;

protected:
	void call_pickup(class IUpgradableShip* other) override;
};

