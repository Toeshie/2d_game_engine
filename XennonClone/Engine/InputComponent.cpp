#include "GameEngine.h"
#include "InputComponent.h"
#include "SDL.h"
#include "Input.h"

input_component::input_component()
{
	GameEngine::add_pawn(this);
}

input_component::~input_component()
{
	GameEngine::remove_pawn(this);
}

void input_component::start()
{
	game_object::start();
}

void input_component::update(float deltaTime)
{
	game_object::update(deltaTime);
}

void input_component::handle_events()
{
	input_right_axis_ = Input::get_right_axis_value();
	input_up_axis_ = Input::get_up_axis_value();
}