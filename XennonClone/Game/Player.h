#pragma once
#include "InputComponent.h"
#include "IUpgradableShip.h"
#include "MulticastDelegate.h"

class PhysicsComponent;
class CircleCollision;
class HealthComponent;

class Player : public input_component, public IUpgradableShip
{
public:
	Player();
	void update(float deltaTime) override;
	void handle_events() override;
	void on_became_visible() override;
	void on_became_hidden() override;

	// IUpgradableShip interface implementation
	void upgrade_shields(int amount_to_heal) override;
	void upgrade_weapon() override;
	void add_companion() override;

	// Health related methods
	void on_zero_health();
	void on_revive();

	// Getters
	bool is_shooting() const { return is_shooting_; }
	HealthComponent* get_health_component() const { return health_component_; }

private:
	// Helper methods
	void on_companion_die(class Companion* companion);
	void move(float delta_time);
	void change_animation();
	Vector2D& calculate_fire_position(int position_multiplier);

	// Components
	class animation_component* animation_component_ = nullptr;
	class Sprite* sprite_component_ = nullptr;
	class HealthComponent* health_component_ = nullptr;
	class AudioComponent* audio_component_ = nullptr;
	PhysicsComponent* physics_component_ = nullptr;
	CircleCollision* collider_ = nullptr;

	// Shooting related
	int bullet_position_multiplier_ = 1;
	bool is_shooting_ = false;
	float fire_rate_ = 0.5f;
	float shots_timer_ = 0.f;
	Vector2D fire_position_;
	int weapon_level_ = 1;

	// Movement
	int move_speed_ = 250;

	// Companion related
	std::vector<Vector2D> companion_positions_ = {Vector2D(100, 0), Vector2D(-100, 0)};
	std::vector<Vector2D> available_positions_;
};

