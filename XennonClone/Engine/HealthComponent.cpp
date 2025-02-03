#include "HealthComponent.h"
#include "MathHelper.h"
#include "GameObject.h"

int HealthComponent::take_damage(int amount)
{
	if (is_dead_)return 0;
	current_health_ = MathHelper::clamp_int(current_health_ - amount, 0, max_health_);

	on_damage_taken.Broadcast(amount);
	if (current_health_ <= 0)
	{
		on_die.Broadcast();
		is_dead_ = true;
	}

	return current_health_;
}

void HealthComponent::deal_damage(HealthComponent* other_health_component, int amount)
{
	if (other_health_component)
	{
		other_health_component->take_damage(amount);
	}
}

void HealthComponent::heal(int ammount)
{
	if (is_dead_)return;
	current_health_ = MathHelper::clamp_int(current_health_ + ammount, 0, max_health_);
	on_heal.Broadcast(ammount);
}

void HealthComponent::respawn()
{
	if (!is_dead_)return;
	is_dead_ = false;
	current_health_ = max_health_;
	on_respawn.Broadcast();
}
