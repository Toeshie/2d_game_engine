#include "SquareCollision.h"
#include "box2d/b2_fixture.h"
#include "PhysicsComponent.h"
#include "box2d/b2_polygon_shape.h"

b2Fixture* SquareCollision::create_fixture()
{
	b2FixtureDef fixture_def;
	fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	
	b2PolygonShape shape;
	shape.SetAsBox(width_, height_);
	shape.m_type = b2Shape::e_polygon;

	fixture_def.shape = &shape;
	fixture_def.isSensor = get_is_trigger();
	fixture_def.friction = get_friction();

	b2Fixture* fixture = phys_comp_->get_b2_body()->CreateFixture(&fixture_def);
	phys_comp_->clear_default_body();

	return fixture;
}

void SquareCollision::update_shape(float width, float height)
{
	if (!my_fixture_) {
		return;
	}
	
	if (auto* shape = static_cast<b2PolygonShape*>(my_fixture_->GetShape())) {
		shape->SetAsBox(width, height);
	}
}

void SquareCollision::set_height(float height)
{
	if (height_ != height) {
		height_ = height;
		update_shape(width_, height_);
	}
}

void SquareCollision::set_width(float width)
{
	if (width_ != width) {
		width_ = width;
		update_shape(width_, height_);
	}
}

void SquareCollision::set_bounds(Vector2D bounds)
{
	if (Vector2D(width_, height_) != bounds) {
		width_ = bounds.x;
		height_ = bounds.y;
		update_shape(width_, height_);
	}
}

void SquareCollision::set_bounds(float width, float height)
{
	if (width_ != width || height_ != height) {
		width_ = width;
		height_ = height;
		update_shape(width_, height_);
	}
}

SquareCollision::SquareCollision(PhysicsComponent* phys_comp, float width, float height)
	: width_(width)
	, height_(height)
{
	phys_comp_ = phys_comp;
}
