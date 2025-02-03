#pragma once
#include "GameObject.h"

// Forward declarations
class Sprite;
class animation_component;
class PhysicsComponent;
class CircleCollision;
class AudioComponent;
class IUpgradableShip;

class BasePickupClass : public game_object
{
public:
	BasePickupClass();
	virtual void update(float deltaTime) override;
	void on_trigger_enter(game_object* other);

	virtual void on_became_hidden() override;
	virtual void on_became_visible() override;
protected:

	bool was_visible_ = false;

	virtual void call_pickup(IUpgradableShip* other) = 0;
	void setup(const char* spritePath, int spriteColumns, int spriteRows, int colliderRadius);
	Sprite* sprite_component_ = nullptr;
	animation_component* animation_component_ = nullptr;
	PhysicsComponent* physics_component_ = nullptr;
	CircleCollision* collider_ = nullptr;
	AudioComponent* audio_component_ = nullptr;
};

