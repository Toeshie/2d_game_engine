#pragma once
#include "GameObject.h"

struct EnemyData
{
	const char* tag = "";
	const char* texture_path = "";
	int sprite_columns = 1;
	int sprite_rows = 1;
	float scale = 1.0f;
	int collider_radius = 20;
	int max_health = 10;
	int enemy_damage = 100;
	int speed = 70;
	int score = 20;

	EnemyData() = default;

	EnemyData(const char* enemy_tag, const char* path, int columns, int rows, float sc, int radius,
		int health, int damage, int spd, int score_value)
	{
		tag = enemy_tag;
		texture_path = path;
		sprite_columns = columns;
		sprite_rows = rows;
		scale = sc;
		collider_radius = radius;
		max_health = health;
		enemy_damage = damage;
		speed = spd;
		score = score_value;
	}
};

class Enemy : public game_object
{
protected:

	void setup();

	class Sprite* sprite_component_ = nullptr;
	class animation_component* animation_component_ = nullptr;
	class PhysicsComponent* physics_component_ = nullptr;
	class CircleCollision* collider_ = nullptr;
	class HealthComponent* health_component_ = nullptr;

	EnemyData enemy_data_;

public:
	Enemy() = default;
	virtual void on_destroyed() override;
	void on_zero_health();
	virtual void on_trigger_enter(game_object* other);
	virtual void on_became_hidden() override;
};

