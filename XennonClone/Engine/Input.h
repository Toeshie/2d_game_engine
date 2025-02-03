#pragma once

union SDL_Event;  // Forward declaration

class Input
{
public:
	Input();
	~Input() = default;  // add explicit destructor

	// Non-static methods
	void receive_input_event(SDL_Event& ev);

	// Static input methods
	static SDL_Event get_input_event();
	static int get_right_axis_value();
	static int get_up_axis_value();
	static bool is_fire_key_down();

private:
	static SDL_Event event_;  // Move static member to private section
};