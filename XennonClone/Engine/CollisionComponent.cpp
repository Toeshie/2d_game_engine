#include "CollisionComponent.h"
#include "box2d/b2_shape.h"
#include "PhysicsComponent.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"

b2Fixture* CollisionComponent::find_my_fixture()
{
	if (!phys_comp_ || !my_fixture_) return nullptr;

	b2Fixture* list = phys_comp_->get_b2_body()->GetFixtureList();
	while (list != my_fixture_)
	{
		list = list->GetNext();
		if (!list)
		{
			return nullptr;
		}
	}
	return list;
}

b2Fixture* CollisionComponent::create_fixture()
{
	if (!phys_comp_) return nullptr;

	b2FixtureDef fixDef;
	fixDef.userData.pointer = (uintptr_t)this;
	
	b2CircleShape shape;
	shape.m_radius = 20;
	shape.m_p = b2Vec2(0, 0);
	shape.m_type = b2Shape::e_circle;
	
	fixDef.shape = &shape;
	fixDef.isSensor = get_is_trigger();
	fixDef.friction = get_friction();

	b2Fixture* fix = phys_comp_->get_b2_body()->CreateFixture(&fixDef);
	phys_comp_->clear_default_body();
	return fix;
}

CollisionComponent::CollisionComponent(PhysicsComponent* physical) :
	phys_comp_(physical),
	my_fixture_(nullptr)
{
}

void CollisionComponent::start()
{
	if (phys_comp_)
	{
		my_fixture_ = create_fixture();
	}
}

CollisionComponent::~CollisionComponent()
{
	if (phys_comp_ && my_fixture_)
	{
		phys_comp_->get_b2_body()->DestroyFixture(my_fixture_);
		my_fixture_ = nullptr;
	}
}

void CollisionComponent::set_is_trigger(bool new_val)
{
	if (!phys_comp_ || !my_fixture_) return;

	b2Fixture* fix = find_my_fixture();
	if (fix)
	{
		is_trigger_ = new_val;
		fix->SetSensor(new_val);
	}
}

void CollisionComponent::set_collision_enabled(bool bNewEnabled)
{
	if (is_enabled_ == bNewEnabled) return;

	b2Fixture* fix = find_my_fixture();
	if (!fix) return;

	fix->SetSensor(bNewEnabled);
	is_enabled_ = bNewEnabled;
}

bool CollisionComponent::get_is_collision_enabled()
{
	return phys_comp_ ? is_collision_enabled_ : false;
}
