#include "UISprite.h"
#include "GameEngine.h"
#include "Renderer.h"
#include "SDL.h"
#include "MathHelper.h"

UISprite::UISprite(const char* sprite_path, int columns, int rows,
                   Vector2D draw_position, float scale, Vector2D sheet_coord)
    : render_component()
    , draw_position_(draw_position)
    , scale_(scale)
    , sheet_coord_(sheet_coord)
    , xy_(0.0f, 0.0f)
{
	is_ui_ = true;
	current_texture_data_ = TextureManager::load_texture_open_gl(sprite_path);
	
	wh_.x = current_texture_data_.sheet_width / columns;
	wh_.y = current_texture_data_.sheet_height / rows;

	GameEngine::add_render_component(this);
}

UISprite::~UISprite()
{
	TextureManager::free_texture_data(&current_texture_data_);
}

void UISprite::render()
{
	if (!get_is_active()) return;

	SDL_Rect source_rect;
	source_rect.x = static_cast<int>(wh_.x * sheet_coord_.x);
	source_rect.y = static_cast<int>(wh_.y * sheet_coord_.y);
	source_rect.w = static_cast<int>(wh_.x * x_fill_);
	source_rect.h = static_cast<int>(wh_.y * y_fill_);

	Renderer::draw_quad(
		draw_position_,
		scale_,
		current_texture_data_.texture_id,
		&source_rect,
		Vector2D(current_texture_data_.sheet_width, current_texture_data_.sheet_height)
	);
}

void UISprite::set_render_scale(float scale)
{
	scale_ = scale;
}

void UISprite::set_x_fill(float amount)
{
	x_fill_ = MathHelper::zero_one(amount);
}

void UISprite::set_y_fill(float amount)
{
	y_fill_ = MathHelper::zero_one(amount);
}

void UISprite::set_sheet_cord(Vector2D cord)
{
	sheet_coord_ = cord;
}