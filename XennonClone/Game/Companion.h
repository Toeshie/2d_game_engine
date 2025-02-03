#pragma once

#include "GameObject.h"
#include "IUpgradableShip.h"
#include "MulticastDelegate.h"

class Player;
class Sprite;
class animation_component;
class PhysicsComponent;
class CircleCollision;
class HealthComponent;

class Companion : public game_object, public IUpgradableShip
{

protected:

	Player* follow_target_ = nullptr;
	Sprite* sprite_component_ = nullptr;
	animation_component* animation_component_ = nullptr;
	PhysicsComponent* phys_component_ = nullptr;
	CircleCollision* collider_component_ = nullptr;
	HealthComponent* health_component_ = nullptr;

	Vector2D player_off_set_;
	Vector2D bullet_position_;

	float fire_rate_ = 0.5f;
	float shots_timer_ = 0.0f;

	int weapon_power_ = 1;

public:

	MulticastDelegate<Companion*> on_companion_die;

	explicit Companion(Vector2D position);
	
	void start() override;
	void update(float delta) override;

	void set_target(Player* newTarget, Vector2D localPosition);
	void on_zero_health();
	void on_player_die();

	virtual void upgrade_shields(int amountToHeal) override;
	virtual void upgrade_weapon() override;
	virtual void add_companion() override {}

	Vector2D GetPositionTarget() { return player_off_set_; }
};

