#pragma once
#include "RenderComponent.h"
#include "Transform.h"
#include "SDL.h"
#include "TextureManager.h"

struct SDL_Texture;
struct SDL_Rect;

class Sprite : public render_component
{
	friend class animation_component;
	friend class parallax_component;
protected:
	Transform* parent_transform_{ nullptr };

	TextureData texture_data_;

	SDL_Rect source_rect_;
	SDL_FRect dest_rect_;

	int sheet_width_ = 0;
	int sheet_height_ = 0;

	int frame_width_ = 1;
	int frame_height_ = 1;

	float rotation_ = 0.f;

	bool flip_x_ = false;
	bool flip_y_ = false;

	float opacity_ = 1;

	float scale_ = 1.f;

public:
	Sprite(const char* texture_path, int render_priority);
	Sprite(const char* texture_path, int render_priority, float scale);
	Sprite(const char* texture_path, int sprite_sheet_columns, int sprite_sheet_rows, float scale, int render_priority);
	Sprite(const char* texture_path, int sprite_sheet_columns, int sprite_sheet_rows, float scale, int render_priority, bool is_ui);

	void set_flip_y(bool val) { flip_y_ = val; }

	virtual void start() override;

	void set_texture_data(const char* texturePath, int spriteSheetColumns, int spriteSheetRows, float scale);

	int get_sheet_height() const { return sheet_height_; }

	SDL_Rect& get_source_rect();

	void set_rotation(float val) { rotation_ = val; }

	void set_opacity(float opacity);
	void set_scale(float fScale);

	float get_scale() const { return scale_; }

	virtual void render() override;

	virtual void on_destroyed() override;
};