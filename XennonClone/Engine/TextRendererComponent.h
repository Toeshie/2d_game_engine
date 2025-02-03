#pragma once
#include "RenderComponent.h"
#include <string>
#include "Transform.h"
#include <vector>

class FontText;  // Forward declaration

class TextRendererComponent : public render_component
{
protected:
	std::string text_;
	float text_scale_ = 1.0f;
	Vector2D text_position_;
	FontText* font_ = nullptr;
	std::vector<Vector2D> text_coords_;
public:	
	TextRendererComponent(std::string TextToRender, float scale, Vector2D pos, std::string font);
	~TextRendererComponent();

	virtual void on_destroyed() override;

	virtual void render() override;

	void set_text(std::string newText);
	void set_scale(float textScale) noexcept { text_scale_ = textScale; }
	void set_position(Vector2D newPosition) noexcept { text_position_ = newPosition; }

	std::string get_text_string() const noexcept { return text_; }
	float get_text_scale() const noexcept { return text_scale_; }
	Vector2D get_text_position() const noexcept { return text_position_; }
};

