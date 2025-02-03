#include "TextRendererComponent.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "SDL.h"
#include "FontLoader.h"

TextRendererComponent::TextRendererComponent(std::string TextToRender, float scale, Vector2D pos, std::string font)
	: render_component()
	, text_position_(pos)
	, text_scale_(scale)
{
	font_ = GameEngine::get_instance()->get_font_loader()->get_font(font);
	text_ = "";
	set_text(TextToRender);
	is_ui_ = true;
	GameEngine::add_render_component(this);
}

TextRendererComponent::~TextRendererComponent()
{
	GameEngine::remove_render_component(this);
}

void TextRendererComponent::on_destroyed()
{
	GameEngine::remove_render_component(this);
}

void TextRendererComponent::render()
{
	if (!font_) return;

	Vector2D posWorld = text_position_;
	const int frame_width = font_->get_data()->sheet_width / font_->get_columns();
	const int frame_height = font_->get_data()->sheet_height / font_->get_rows();

	for (const auto& coord : text_coords_) {
		SDL_Rect source_rect;
		source_rect.x = frame_width * coord.x;
		source_rect.y = frame_height * coord.y;
		source_rect.w = frame_width;
		source_rect.h = frame_height;

		Renderer::draw_quad(
			posWorld,
			text_scale_,
			font_->get_data()->texture_id,
			&source_rect,
			Vector2D(font_->get_data()->sheet_width, font_->get_data()->sheet_height)
		);

		posWorld.x += frame_width;
	}
}

void TextRendererComponent::set_text(std::string newText)
{
	if (newText == text_) {
		return;
	}

	text_ = newText;
	text_coords_.clear();

	if (font_) {
		for (const char& c : text_) {
			Vector2D index_pos = font_->get_position_index_for_char(c);
			text_coords_.push_back(index_pos);
		}
	}
}
