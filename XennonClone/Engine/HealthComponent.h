#pragma once
#include "Component.h"
#include "MulticastDelegate.h"

class HealthComponent : public Component
{
public:
	// Delegates for health events
	MulticastDelegate<int> on_damage_taken;
	MulticastDelegate<> on_respawn;
	MulticastDelegate<> on_die;
	MulticastDelegate<int> on_heal;

	explicit HealthComponent(int max_health) 
		: max_health_{ max_health }
		, current_health_{ max_health }
		, is_dead_{ false } 
	{}

	// Health manipulation methods
	int take_damage(int amount);  // Returns the health left
	void deal_damage(class HealthComponent* other_health_component, int amount);
	void heal(int ammount);
	void respawn();

	// Getters
	bool get_is_alive() const { return !is_dead_; }
	int get_max_health() const { return max_health_; }
	int get_current_health() const { return current_health_; }

private:
	bool is_dead_{ false };
	int max_health_{ 100 };
	int current_health_{ 100 };
};

