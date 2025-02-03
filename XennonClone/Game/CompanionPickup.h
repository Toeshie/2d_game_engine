#pragma once

#include "BasePickupClass.h"

class IUpgradableShip;

class CompanionPickup : public BasePickupClass
{
public:
	CompanionPickup();
	virtual void start() override;
protected:
	virtual void call_pickup(IUpgradableShip* other) override;
};

