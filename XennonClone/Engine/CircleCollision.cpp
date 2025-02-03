#include "CircleCollision.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_circle_shape.h"
#include "GameObject.h"

b2Fixture* CircleCollision::create_fixture()
{
	if (!phys_comp_) return nullptr;

	b2FixtureDef fixDef;
	fixDef.userData.pointer = (uintptr_t)this;
	
	b2CircleShape shape;
	shape.m_radius = radius_;
	shape.m_p = b2Vec2(0, 0);
	shape.m_type = b2Shape::e_circle;
	
	fixDef.shape = &shape;
	fixDef.isSensor = get_is_trigger();
	fixDef.friction = get_friction();
	
	b2Fixture* fix = phys_comp_->get_b2_body()->CreateFixture(&fixDef);
	phys_comp_->clear_default_body();
	return fix;
}

CircleCollision::CircleCollision(PhysicsComponent* physComp) : 
	CollisionComponent(physComp),
	radius_(2.f)
{
	phys_comp_ = physComp;
}

CircleCollision::CircleCollision(PhysicsComponent* physComp, float radius) :
	CollisionComponent(physComp),
	radius_(radius)
{
	phys_comp_ = physComp;
}

void CircleCollision::set_radius(float radius)
{
	if (!my_fixture_) return;
	if (radius_ == radius) return;
	
	radius_ = radius;
	b2CircleShape* shape = static_cast<b2CircleShape*>(my_fixture_->GetShape());
	if (shape)
	{
		shape->m_radius = radius_;
	}
}
