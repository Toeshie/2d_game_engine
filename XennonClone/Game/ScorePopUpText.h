#pragma once
#include "GameObject.h"
#include <string>

class ScorePopUpText : public game_object
{
public:
	ScorePopUpText(std::string text, float time, Vector2D pos);
	void start() override;
	void update(float delta) override;

private:
	class TextRendererComponent* text_ = nullptr;
	float wait_time_ = 3.f;
	std::string render_text_;
};

