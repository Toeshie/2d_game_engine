#pragma once

#include "CollisionComponent.h"

class CircleCollision : public CollisionComponent
{
protected:
	float radius_ = 100.f;

protected:
	virtual class b2Fixture* create_fixture() override;
public:

	CircleCollision() = default;

	CircleCollision(PhysicsComponent* phys_comp);

	CircleCollision(PhysicsComponent* phys_comp, float radius);

	void set_radius(float radius);
	inline float get_radius() const { return radius_; }
};

