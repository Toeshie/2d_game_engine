#pragma once
#include "GameObject.h"
#include <vector>	
#include "Transform.h"

class UISprite;

class PlayerHealthUI : public game_object
{
public:
	void start() override;
	void set_player_life_count(int count);
	void set_player_health(int current, int max);

private:
	// UI Components
	UISprite* life_one_ = nullptr;
	UISprite* life_two_ = nullptr;
	UISprite* life_three_ = nullptr;
	UISprite* health_bar_ = nullptr;
	UISprite* healthbar_back_background_ = nullptr;

	// UI Positioning
	Vector2D starting_life_position_ = Vector2D(20, 430);
};

