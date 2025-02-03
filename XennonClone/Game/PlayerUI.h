#pragma once
#include "GameObject.h"
#include <vector>
#include <string>

class TextRendererComponent;

class PlayerUI : public game_object
{
public:
	void start() override;
	void set_current_score(int score);
	void set_high_score(int score);

private:
	std::string get_number_formated(int num);

	// UI Components
	TextRendererComponent* high_score_text_ = nullptr;
	TextRendererComponent* score_text_ = nullptr;
	TextRendererComponent* player_name_ = nullptr;
};

