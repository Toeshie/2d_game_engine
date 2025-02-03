#pragma once
#include "GameObject.h"

class input_component : public game_object
{
public:
	input_component();
	virtual ~input_component() override;

	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void handle_events();

	int get_input_right_axis() const { return input_right_axis_; }
	int get_input_up_axis() const { return input_up_axis_; }
	int get_move_speed() const { return move_speed_; }

protected:
	int input_right_axis_ = 0;
	int input_up_axis_ = 0;
	int move_speed_ = 110;
};

