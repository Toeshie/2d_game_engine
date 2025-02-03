#pragma once
#include "GameObject.h"

struct BulletData
{
	const char* texture_path = "";
	int rows = 1;
	int columns = 1;
	int damage = 20;
	const char* remove_tag = "";
	int radius = 10;
	float scale = 1.0f;
	int speed = 1000;
	Vector2D direction = Vector2D::up();

	BulletData() = default;

	BulletData(const char* sprite_path, int sprite_rows, int sprite_columns, int bullet_damage,
		const char* destroy_tag, int rad, float sc, int movement_speed, const Vector2D& direction_to_move)
		: texture_path(sprite_path)
		, rows(sprite_rows)
		, columns(sprite_columns)
		, damage(bullet_damage)
		, remove_tag(destroy_tag)
		, radius(rad)
		, scale(sc)
		, speed(movement_speed)
		, direction(direction_to_move)
	{}
};


class BaseBulletClass : public game_object
{
public:
	BaseBulletClass() = default;

	virtual void update(float deltaTime) override;
	virtual void on_trigger_enter(game_object* other);
	virtual void on_became_hidden() override;
	class PhysicsComponent* get_physics_component() const { return physics_component_; }

protected:

	void setup();

	BulletData bullet_data_;

	class animation_component* animation_component_ = nullptr;
	class PhysicsComponent* physics_component_ = nullptr;
};

