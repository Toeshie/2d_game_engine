#include "ScorePopUpText.h"
#include "TextRendererComponent.h"
#include "GameWorld.h"

ScorePopUpText::ScorePopUpText(std::string text, float time, Vector2D pos)
{
	render_text_ = text;
	wait_time_ = time;
	get_transform()->set_position(pos);
}

void ScorePopUpText::start()
{
	text_ = add_component<TextRendererComponent>(
		render_text_,
		1,
		get_transform()->get_position(),
		"png/font8x8.png"
	);
}

void ScorePopUpText::update(float delta)
{
	wait_time_ -= delta;
	if (wait_time_ <= 0) {
		game_world::destroy_object(this);
	}
}
