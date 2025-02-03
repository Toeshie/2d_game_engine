#include "BaseBulletClass.h"
#include "Sprite.h"
#include "PhysicsComponent.h"
#include "CircleCollision.h"
#include "HealthComponent.h"
#include "GameWorld.h"
#include "AnimationComponent.h"
#include "Enemy.h"
#include "Explosion.h"

void BaseBulletClass::setup()
{
	add_component<Sprite>(bullet_data_.texture_path, bullet_data_.columns, bullet_data_.rows, 
		bullet_data_.scale, 0);
	animation_component_ = add_component<animation_component>(get_component<Sprite>(), false, 8.0f);
	physics_component_ = add_component<PhysicsComponent>(BodyType::dynamic, 0, 1, 1);
	CollisionComponent* comp = add_component<CircleCollision>(get_component<PhysicsComponent>(), bullet_data_.radius);
	comp->set_is_trigger(true);
	comp->on_trigger_enter.Add(this, &BaseBulletClass::on_trigger_enter);

	get_component<Sprite>()->set_is_visible(true);
}


void BaseBulletClass::update(float deltaTime)
{
	get_component<PhysicsComponent>()->set_velocity(bullet_data_.direction * bullet_data_.speed);
	game_object::update(deltaTime);
}

void BaseBulletClass::on_trigger_enter(game_object* other)
{
	if (other->has_tag(bullet_data_.remove_tag))
	{
		HealthComponent* otherHealthComp = other->get_component<HealthComponent>();
		int otherHealthLeft = 0;
		if (otherHealthComp) {
			otherHealthLeft = otherHealthComp->take_damage(bullet_data_.damage);
		}

		if (otherHealthLeft > 0)
		{
			game_world::instantiate_object<Explosion>()->transform.set_position(transform.get_position());
		}

		game_world::destroy_object(this);
	}
}

void BaseBulletClass::on_became_hidden()
{
	game_world::destroy_object(this);
}

