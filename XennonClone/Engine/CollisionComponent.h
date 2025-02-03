#pragma once

#include "Component.h"
#include "MulticastDelegate.h"

class CollisionComponent : public Component
{
protected:
	class PhysicsComponent* phys_comp_ = nullptr;
	class b2Fixture* my_fixture_ = nullptr;

	float friction_ = 1;
	bool is_enabled_ = true;
	bool is_trigger_ = false;
	bool is_collision_enabled_ = true;

protected:
	
	b2Fixture* find_my_fixture();

	virtual b2Fixture* create_fixture();
public:

	MulticastDelegate<game_object*> on_collision_enter;
	MulticastDelegate<game_object*> on_collision_exit;
	MulticastDelegate<game_object*> on_trigger_enter;
	MulticastDelegate<game_object*> on_trigger_exit;
	CollisionComponent() = default;

	CollisionComponent(PhysicsComponent* physical);
	virtual ~CollisionComponent();

	virtual void start() override;

	void set_is_trigger(bool new_val);

	inline float get_friction() const { return friction_; }

	void set_collision_enabled(bool bNewEnabled);

	inline bool get_is_trigger() const { return is_trigger_; }
	bool get_is_collision_enabled();

	inline PhysicsComponent* get_phys_comp() const { return phys_comp_; }
	inline b2Fixture* get_fixture() const { return my_fixture_; }
};

