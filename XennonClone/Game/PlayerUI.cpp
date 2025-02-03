#include "PlayerUI.h"
#include "TextRendererComponent.h"
#include <sstream>
#include <iomanip>

std::string PlayerUI::get_number_formated(int num)
{
	std::stringstream ss;
	ss << std::setw(10) << std::setfill('0') << num;
	return ss.str();
}

void PlayerUI::start()
{
	high_score_text_ = add_component<TextRendererComponent>(
		"Player Health: '", 
		1.f, 
		Vector2D(350, 20), 
		"png/font8x8.png"
	);
	high_score_text_->set_text("Player Score: 100'00");

	player_name_ = add_component<TextRendererComponent>(
		"Player", 
		1.f, 
		Vector2D(10, 20), 
		"png/font8x8.png"
	);

	score_text_ = add_component<TextRendererComponent>(
		"0000000000", 
		1.f, 
		Vector2D(10, 50), 
		"png/font16x16.png"
	);
}

void PlayerUI::set_current_score(int score)
{
	score_text_->set_text(get_number_formated(score));
}

void PlayerUI::set_high_score(int score)
{
	high_score_text_->set_text("High score: " + get_number_formated(score));
}
