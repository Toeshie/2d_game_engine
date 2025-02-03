#include "PhysicsWorld.h"
#include "box2d/b2_world.h"
#include "CollisionListener.h"
#include "box2d/b2_body.h"

physics_world* physics_world::instance_ = nullptr;

physics_world::~physics_world() {
	delete b2_world_;
	delete listener_;
}

void physics_world::init() {
	if (instance_) {
		delete this;
		return;
	}
	
	instance_ = this;
	listener_ = new CollisionListener();
	b2_world_ = new b2World(b2Vec2(0.0f, -10.0f));
	b2_world_->SetContactListener(listener_);
}

void physics_world::set_gravity(Vector2D gravity_direction) {
	if (b2_world_) {
		b2_world_->SetGravity(b2Vec2(gravity_direction.x, gravity_direction.y));
	}
}

void physics_world::update_physics(float delta) {
	if (b2_world_) {
		b2_world_->Step(delta, 8, 8);
	}
}

void physics_world::execute_stashed_events() {
	if (listener_) {
		listener_->execute_handles();
	}
}

b2Body* physics_world::create_body(const b2BodyDef& def) {
	if (!b2_world_) {
		return nullptr;
	}
	return b2_world_->CreateBody(&def);
}

void physics_world::destroy_body(b2Body* body_to_destroy) {
	if (b2_world_ && body_to_destroy) {
		b2_world_->DestroyBody(body_to_destroy);
	}
}