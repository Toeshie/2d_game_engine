#include "PlayerHealthUI.h"
#include "UISprite.h"
#include "GameWorld.h"

void PlayerHealthUI::start()
{
	// Initialize life indicators
	life_one_ = add_component<UISprite>("png/ship1.png", 7, 1, 
		starting_life_position_ + Vector2D(0.5f, 240), .5f, Vector2D(0, 0));
	life_two_ = add_component<UISprite>("png/ship1.png", 7, 1, 
		starting_life_position_ + Vector2D(40, 240), .5f, Vector2D(0, 0));
	life_three_ = add_component<UISprite>("png/ship1.png", 7, 1, 
		starting_life_position_ + Vector2D(80, 240), .5f, Vector2D(0, 0));

	// Initialize health bar
	healthbar_back_background_ = add_component<UISprite>("png/healthbarback.png", 1, 1, 
		Vector2D(20, 690), 1.5f, Vector2D(0, 0));
	health_bar_ = add_component<UISprite>("png/Healthbar.png", 1, 1, 
		Vector2D(20, 690), 1.5f, Vector2D(0, 0));
}

void PlayerHealthUI::set_player_life_count(int count)
{
	switch (count)
	{
	case 1:
		life_one_->set_active(true);
		life_two_->set_active(false);
		life_three_->set_active(false);
		break;
	case 2:
		life_one_->set_active(true);
		life_two_->set_active(true);
		life_three_->set_active(false);
		break;
	case 3:
		life_one_->set_active(true);
		life_two_->set_active(true);
		life_three_->set_active(true);
		break;
	case 0:
	default:
		life_one_->set_active(false);
		life_two_->set_active(false);
		life_three_->set_active(false);
		break;
	}
}

void PlayerHealthUI::set_player_health(int current, int max)
{
	health_bar_->set_x_fill((float)current / max);
}
