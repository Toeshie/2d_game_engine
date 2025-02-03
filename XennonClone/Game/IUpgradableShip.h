#pragma once

class IUpgradableShip
{
public:
	virtual ~IUpgradableShip() = default;
	
	virtual void upgrade_shields(int amount_to_heal) = 0;
	virtual void upgrade_weapon() = 0;
	virtual void add_companion() = 0;
};
