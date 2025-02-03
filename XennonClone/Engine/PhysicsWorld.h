#pragma once

#include "Transform.h"

// Forward declarations
class b2World;
class b2Body;
struct b2BodyDef;
class CollisionListener;

class physics_world
{
private:
	static physics_world* instance_;
	
	b2World* b2_world_ = nullptr;
	CollisionListener* listener_ = nullptr;

public:
	physics_world() = default;
	~physics_world();

	// Delete copy constructor and assignment operator for singleton
	physics_world(const physics_world&) = delete;
	physics_world& operator=(const physics_world&) = delete;

	void init();

	b2World* get_world() const noexcept { return b2_world_; }

	void set_gravity(Vector2D gravity_direction);

	void update_physics(float delta);

	static physics_world* get_instance() noexcept { return instance_; }

	void execute_stashed_events();

	b2Body* create_body(const b2BodyDef& def);
	void destroy_body(b2Body* body_to_destroy);
};

