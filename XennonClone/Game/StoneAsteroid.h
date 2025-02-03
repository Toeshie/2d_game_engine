#pragma once
#include "Enemy.h"

enum class AsteroidType
{
	Small,
	Medium,
	Large
};

class StoneAsteroid : public Enemy
{
public:
	StoneAsteroid();
	explicit StoneAsteroid(AsteroidType asteroidType);
	virtual void update(float deltaTime) override;
	virtual void on_destroyed() override;

	Vector2D movement_direction = Vector2D::down();

	virtual void on_became_hidden() override;

	void set_asteroid_type(AsteroidType type) { asteroid_type_ = type; setup(); }
	AsteroidType get_asteroid_type() const { return asteroid_type_; }
	const char* get_asteroid_type_string() const {
		switch (asteroid_type_) {
		case AsteroidType::Small:  return "Small";
		case AsteroidType::Medium: return "Medium";
		case AsteroidType::Large:  return "Large";
		default:                   return "Unknown";
		}
	}

private:
	void asteroid_data();
	AsteroidType asteroid_type_ = AsteroidType::Small;
};

