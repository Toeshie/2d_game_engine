#pragma once
#include "BaseBulletClass.h"

class PlayerBullet : public BaseBulletClass
{
public:
	PlayerBullet();
	void start() override;
};

