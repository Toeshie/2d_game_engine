#pragma once
#include "Component.h"
#include "Transform.h"

//Body type for Box2D physics
enum BodyType {

	dynamic,
	kinematic,
	Static,
};

class PhysicsComponent : public Component
{
protected:
	class b2Fixture* body_fixture_ = nullptr;

	class b2Body* stored_body_ = nullptr;
	Transform* parent_transform_ = nullptr;

	Vector2D position_;
	Vector2D linear_velocity_;
	BodyType body_type_ = BodyType::dynamic;

	float gravity_ = 1;
	float mass_ = 1;
	float density_ = 1;

	bool start_enabled_ = true;
	bool enabled_ = true;
	bool fixed_rotation_ = true; //prevent body from rotating
	bool continuous_collision_ = true; //prevent tunneling
	bool allow_sleep_ = false; //If body can sleep 

protected:
	void build_body();
	void build_default_fixture();
public:
	PhysicsComponent() {};
	PhysicsComponent(BodyType type, float gravity, float mass, float density);
	~PhysicsComponent();
	
	virtual void on_destroyed() override;
	virtual void start() override;

	void set_velocity(Vector2D velocity);
	void add_force(Vector2D velocity);
	void clear_velocity();
	Vector2D get_velocity();
	bool get_is_body_awake();

	void set_gravity_scale(float scale);

	void set_position(Vector2D position);
	void set_position(float x, float y);

	Vector2D get_position();

	virtual void update(float deltatime) override;

	void set_body_type(BodyType new_type);

	b2Body* get_b2_body() { return stored_body_; }

	void clear_default_body();
};

