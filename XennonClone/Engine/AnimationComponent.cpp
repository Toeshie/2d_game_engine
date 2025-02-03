#include "AnimationComponent.h"
#include "Sprite.h"
#include "SDL.h"
#include "GameObject.h"

void animation_component::start()
{
	if (!parent_sprite_component_) return;
	
	if (is_animation_playing_)
	{
		initial_animation_frame_x_ = 0;
		initial_animation_frame_y_ = 0;
		final_animation_frame_x_ = parent_sprite_component_->sheet_width_;
		final_animation_frame_y_ = parent_sprite_component_->sheet_height_;
	}
}

void animation_component::update(float deltatime)
{
	if (!parent_sprite_component_ || !is_animation_playing_)
	{
		frame_time_ = 0;
		return;
	}

	SDL_Rect& spriteSourceRect = parent_sprite_component_->get_source_rect();
	frame_time_ += deltatime;

	if (frame_time_ < (1.f / animation_speed_))
	{
		return;
	}

	spriteSourceRect.x += parent_sprite_component_->frame_width_;
	frame_time_ = 0.f;

	if (spriteSourceRect.x < final_animation_frame_x_)
	{
		return;
	}

	float nextSourceRectY = spriteSourceRect.y + parent_sprite_component_->frame_height_;

	// Handle X position
	if (is_animation_looping_)
	{
		spriteSourceRect.x = initial_animation_frame_x_;
	}
	else if (nextSourceRectY < final_animation_frame_y_)
	{
		spriteSourceRect.x = initial_animation_frame_x_;
	}
	else
	{
		spriteSourceRect.x = final_animation_frame_x_ - parent_sprite_component_->frame_width_;
		on_animation_ended.Broadcast();
	}

	// Handle Y position
	spriteSourceRect.y = nextSourceRectY;
	if (spriteSourceRect.y >= final_animation_frame_y_)
	{
		spriteSourceRect.y = is_animation_looping_ ? 
			initial_animation_frame_y_ : 
			final_animation_frame_y_ - parent_sprite_component_->frame_height_;
	}
}

void animation_component::play_animation(int starting_frame_row, int starting_frame_column, int ending_frame_row, int ending_frame_column, bool can_loop_animation)
{
	if (!parent_sprite_component_) return;
	
	stop_animation();

	const int frame_width = parent_sprite_component_->frame_width_;
	const int frame_height = parent_sprite_component_->frame_height_;

	// Calculate frame positions
	initial_animation_frame_x_ = starting_frame_column * frame_width;
	initial_animation_frame_y_ = starting_frame_row * frame_height;
	final_animation_frame_x_ = (ending_frame_column + 1) * frame_width;
	final_animation_frame_y_ = (ending_frame_row + 1) * frame_height;

	// Set initial frame position
	SDL_Rect& spriteSourceRect = parent_sprite_component_->get_source_rect();
	spriteSourceRect.x = initial_animation_frame_x_;
	spriteSourceRect.y = initial_animation_frame_y_;

	is_animation_playing_ = true;
	is_animation_looping_ = can_loop_animation;
}

bool animation_component::is_playing_animation(int starting_frame_row, int starting_frame_column, int ending_frame_row, int ending_frame_column) const
{
	return initial_animation_frame_x_ == starting_frame_column * parent_sprite_component_->frame_width_ &&
		initial_animation_frame_y_ == starting_frame_row * parent_sprite_component_->frame_height_ &&
		final_animation_frame_x_ == (ending_frame_column * parent_sprite_component_->frame_width_) + parent_sprite_component_->frame_width_ &&
		final_animation_frame_y_ == (ending_frame_row * parent_sprite_component_->frame_height_) + parent_sprite_component_->frame_height_;
}
