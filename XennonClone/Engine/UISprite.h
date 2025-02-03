#pragma once
#include "RenderComponent.h"
#include "TextureManager.h"
#include "Transform.h"


class UISprite : public render_component
{
protected:

	Vector2D draw_position_ = Vector2D::zero();
	Vector2D wh_;
	Vector2D xy_;
	Vector2D sheet_coord_;

	TextureData current_texture_data_;
	float scale_ = 1.0f;

	float x_fill_ = 1.0f;
	float y_fill_ = 1.0f;

public:

	UISprite(const char* sprite_path, int columns, int rows, Vector2D draw_position, float scale, Vector2D sheet_coord);

	~UISprite();

	void render() override;

	void set_render_scale(float scale);

	void set_x_fill(float amount);
	void set_y_fill(float amount);

	void set_sheet_cord(Vector2D cord);


};

