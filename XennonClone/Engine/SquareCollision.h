#pragma once

#include "CollisionComponent.h"
#include "Transform.h"

class PhysicsComponent;  // Forward declaration

class SquareCollision : public CollisionComponent
{
protected:
	float height_ = 1.0f;
	float width_ = 1.0f;

	b2Fixture* create_fixture() override;
	void update_shape(float width, float height);

public:
	SquareCollision(PhysicsComponent* phys_comp, float width, float height);

	float get_height() const noexcept { return height_; }
	float get_width() const noexcept { return width_; }

	void set_height(float height);
	void set_width(float width);

	void set_bounds(Vector2D bounds);
	void set_bounds(float width, float height);
};

