
#include "Sprite.h"
#include "GameObject.h"
#include "SDL.h"
#include "Transform.h"
#include "GameEngine.h"
#include "MathHelper.h"
#include "TextureManager.h"
#include "Renderer.h"

Sprite::Sprite(const char* texture_path, int render_priority) : render_component(render_priority)
{
	set_texture_data(texture_path, 1, 1, 1.f);
}

Sprite::Sprite(const char* texture_path, int render_priority, float scale) : render_component(render_priority)
{
	set_texture_data(texture_path, 1, 1, scale);
}

Sprite::Sprite(const char* texture_path, int spriteSheetRows, int spriteSheetColumns, 
	float scale, int render_priority) : render_component(render_priority)
{
	set_texture_data(texture_path, spriteSheetRows, spriteSheetColumns, scale);
}

Sprite::Sprite(const char* texture_path, int sprite_sheet_columns, int sprite_sheet_rows, float scale, int render_priority, bool is_ui) : render_component()
{
	set_texture_data(texture_path, sprite_sheet_rows, sprite_sheet_columns, scale);
	render_priority_ = render_priority;
	is_ui_ = is_ui;
	GameEngine::add_render_component(this);
}

void Sprite::start()
{
	Component::start();

	if (component_owner_)
	{
		parent_transform_ = component_owner_->get_transform();
	}

}

void Sprite::set_opacity(float opacity)
{
	opacity_ = MathHelper::zero_one(opacity);
}

void Sprite::set_scale(float fScale)
{
	scale_ = fScale;
}

void Sprite::render()
{
	if (!is_active_)return;
	if (parent_transform_)
	{
		SDL_FPoint center;
		center.x = 0;
		center.y = 0;

		SDL_RendererFlip flip = (flip_y_ ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

		Renderer::draw_quad(parent_transform_->get_position(), scale_, texture_data_.texture_id,
			&source_rect_, Vector2D(texture_data_.sheet_width, texture_data_.sheet_height));

	}
}

void Sprite::on_destroyed()
{
	GameEngine::remove_render_component(this);
	TextureManager::free_texture_data(&texture_data_);
}


void Sprite::set_texture_data(const char* texturePath, int spriteSheetRows, int spriteSheetColumns, float scale)
{
	texture_data_ = TextureManager::load_texture_open_gl(texturePath);

	sheet_width_ = texture_data_.sheet_width;
	sheet_height_ = texture_data_.sheet_height;

	frame_width_ = sheet_width_ / spriteSheetRows;
	frame_height_ = sheet_height_ / spriteSheetColumns;
	scale_ = scale;

	source_rect_.x = source_rect_.y = 0;
	source_rect_.w = frame_width_;
	source_rect_.h = frame_height_;
	
}

SDL_Rect& Sprite::get_source_rect()
{
	return source_rect_;
}

