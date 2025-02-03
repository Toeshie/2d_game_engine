
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "PhysicsWorld.h"
#include "CollisionComponent.h"
#include "box2d\b2_body.h"
#include "box2d\b2_fixture.h"
#include "box2d\b2_circle_shape.h"
#include "box2d\b2_shape.h"

PhysicsComponent::PhysicsComponent(BodyType type, float gravity, float mass, float density) {
	body_type_ = type;
	gravity = gravity;
	mass_ = mass;
	density_ = density;
}

PhysicsComponent::~PhysicsComponent()
{
	b2Fixture* fix = stored_body_->GetFixtureList();
	do {
		if (fix) {
			b2Fixture* temp = fix;
			fix = fix->GetNext();
			stored_body_->DestroyFixture(temp);
		}
	} while (fix != nullptr);
	physics_world::get_instance()->destroy_body(stored_body_);
}

void PhysicsComponent::on_destroyed()
{
	
}

void PhysicsComponent::start()
{
	Component::start();

	parent_transform_ = get_owner_game_object()->get_transform();

	build_body();
	build_default_fixture();
}

void PhysicsComponent::set_velocity(Vector2D velocity)
{	
	linear_velocity_ = velocity;

	b2Vec2 vec;
	vec.x = linear_velocity_.x;
	vec.y = -linear_velocity_.y;
	
	stored_body_->SetLinearVelocity(vec);

}

void PhysicsComponent::set_gravity_scale(float scale)
{
	stored_body_->SetGravityScale(scale);
}

void PhysicsComponent::add_force(Vector2D velocity)
{
}

void PhysicsComponent::clear_velocity()
{
	linear_velocity_ = Vector2D::zero();
	stored_body_->SetLinearVelocity(b2Vec2(0, 0));
}

Vector2D PhysicsComponent::get_velocity()
{
	const b2Vec2 vel = stored_body_->GetLinearVelocity();
	return Vector2D(vel.x,vel.y);
}

bool PhysicsComponent::get_is_body_awake()
{
	return stored_body_->IsAwake();
}

void PhysicsComponent::set_position(Vector2D position)
{
	stored_body_->SetTransform(b2Vec2(position.x,-position.y), 0);
	parent_transform_->set_position(position);
}

void PhysicsComponent::set_position(float x, float y)
{
	stored_body_->SetTransform(b2Vec2(x, y), 0);
	parent_transform_->set_position(Vector2D(x,y));
}

Vector2D PhysicsComponent::get_position()
{
	return Vector2D(stored_body_->GetPosition().x, stored_body_->GetPosition().y);
}

void PhysicsComponent::update(float deltatime)
{
	const b2Vec2 pos = stored_body_->GetPosition();
	parent_transform_->set_position(Vector2D(pos.x, -pos.y));
}

void PhysicsComponent::set_body_type(BodyType new_type)
{
	if (new_type !=body_type_) {
		body_type_ = new_type;

		switch (body_type_)
		{
		case dynamic:
			stored_body_->SetType(b2_dynamicBody);
			break;
		case kinematic:
			stored_body_->SetType(b2_kinematicBody);
			break;
		case Static:
			stored_body_->SetType(b2_staticBody);
			break;
		}

	}
}

void PhysicsComponent::clear_default_body()
{
	if (body_fixture_) {
		stored_body_->DestroyFixture(body_fixture_);
	}
}

void PhysicsComponent::build_body()
{
	physics_world* const world = physics_world::get_instance();
	if (!world) {
		return;
	}
	b2BodyDef def;

	def.userData.pointer = (uintptr_t)this; //Could be the user?

	switch (body_type_)
	{
		break;
	case kinematic:
		def.type = b2_kinematicBody;
		break;
	case Static:
		def.type = b2_staticBody;
		break;
	case dynamic:
	default:
		def.type = b2_dynamicBody;
		break;
	}
	def.gravityScale = gravity_;
	def.awake = start_enabled_;
	def.enabled = true;
	def.allowSleep = false;
	Vector2D pos = component_owner_->get_transform()->get_position();

	def.position = b2Vec2(pos.x, pos.y);


	b2BodyUserData data;

	data.pointer = (uintptr_t)this;

	def.userData = data;

	def.bullet = continuous_collision_;

	stored_body_ = world->create_body(def);
}

void PhysicsComponent::build_default_fixture()
{
	if (stored_body_) 
	{
		b2FixtureDef fixDef;
		fixDef.userData.pointer = (uintptr_t)this;
		fixDef.density = density_;
		b2CircleShape Circle;
		Circle.m_radius = 2;
		fixDef.shape = &Circle;
		fixDef.isSensor = true;
		fixDef.friction = 0;
		stored_body_->CreateFixture(&fixDef);
		
	}
}
