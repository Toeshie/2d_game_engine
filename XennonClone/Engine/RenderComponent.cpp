#include "GameEngine.h"
#include "RenderComponent.h"

render_component::render_component()
	: render_priority_(0)
{
}

render_component::render_component(int render_priority)
	: render_priority_(render_priority)
{
	GameEngine::add_render_component(this);
}

render_component::~render_component()
{
	GameEngine::remove_render_component(this);
}

void render_component::set_render_priority(int render_priority)
{
	if (render_priority_ == render_priority) return;
	
	render_priority_ = render_priority;
	GameEngine::sort_render_components();
}
