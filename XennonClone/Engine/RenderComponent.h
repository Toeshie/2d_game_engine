#pragma once
#include "Component.h"

class render_component : public Component
{
public:
	render_component();
	render_component(int render_priority);
	~render_component();

	virtual void render() = 0;

	int get_render_priority() const noexcept { return render_priority_; }
	void set_render_priority(int render_priority);

	void set_is_visible(bool val) noexcept { is_visible_ = val; }
	bool get_is_visible() const noexcept { return is_visible_; }

	bool get_is_ui() const noexcept { return is_ui_; }

protected:
	int render_priority_ = 0;

	bool is_visible_ = true;
	bool is_ui_ = false;

};