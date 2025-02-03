#include "BackgroundStatic.h"
#include "Sprite.h"
#include "GameEngine.h"

BackgroundStatic::BackgroundStatic() : game_object() 
{
	sprite_component_ = add_component<Sprite>("galaxy2.png", -2);
}

void BackgroundStatic::start()
{
	transform.set_position(0.0f, sprite_component_->get_sheet_height());
}

BackgroundStatic::~BackgroundStatic()
{
	delete sprite_component_;
}