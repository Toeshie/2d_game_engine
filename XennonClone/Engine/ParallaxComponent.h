#pragma once
#include "Component.h"

class Sprite;

class parallax_component : public Component
{
public:
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void on_destroyed() override;

	float get_speed() const noexcept { return speed_; }
	void set_speed(float speed) noexcept { speed_ = speed; }

private:
	float speed_ = 50.f;

	Sprite* sprite_component_ = nullptr;
};

