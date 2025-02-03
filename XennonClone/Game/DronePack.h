#pragma once
#include "GameObject.h"

class DronePack : public game_object
{
public:
	virtual void update(float deltaTime) override;

private:
	int number_drones_to_spawn_ = 6;
	float time_between_spawns_ = 0.30f;
	float spawns_timer_ = time_between_spawns_;
};

