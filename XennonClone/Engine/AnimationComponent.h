#pragma once
#include "Component.h"
#include "MulticastDelegate.h"

class animation_component : public Component
{
public:
	MulticastDelegate<> on_animation_ended;

	animation_component(class Sprite* sprite_component, bool auto_play_animation, float animation_speed) :
		parent_sprite_component_{ sprite_component },
		animation_speed_{ animation_speed },
		is_animation_playing_{ auto_play_animation },
		initial_animation_frame_x_{ 0 },
		initial_animation_frame_y_{ 0 },
		final_animation_frame_x_{ 0 },
		final_animation_frame_y_{ 0 },
		is_animation_looping_{ true },
		frame_time_{ 0.f }
	{};

	virtual void start() override;
	virtual void update(float deltatime) override;

	inline void set_animation_looping(const bool value) { is_animation_looping_ = value; }
	inline void stop_animation() { is_animation_playing_ = false; }
	inline void set_animation_speed(float val) { animation_speed_ = val; }

	void play_animation(int starting_frame_row, int starting_frame_column, int ending_frame_row,
		int ending_frame_column, bool can_loop_animation);

	bool is_playing_animation(int starting_frame_row, int starting_frame_column, int ending_frame_row,
		int ending_frame_column) const;

private:
	class Sprite* parent_sprite_component_;
	float animation_speed_;
	bool is_animation_playing_;
	int initial_animation_frame_x_;
	int initial_animation_frame_y_;
	int final_animation_frame_x_;
	int final_animation_frame_y_;
	bool is_animation_looping_;
	float frame_time_;
};

