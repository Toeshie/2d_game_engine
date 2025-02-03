#include "GameEngine.h"
#include "GameObject.h"
#include "Component.h"
#include <algorithm>

game_object::game_object() 
{
	transform = Transform(0, 0, 1, 1);
}

game_object::game_object(Transform transform) 
{
	this->transform = transform;
}

game_object::game_object(Vector2D position, Vector2D scale) {
	transform = Transform(position, scale);
}

game_object::~game_object() 
{
}

void game_object::start()
{
	if (was_initialized_) { return; }
	was_initialized_ = true;
}

bool game_object::has_tag(const std::string& tag) {
	return std::find(game_object_tags_.begin(), game_object_tags_.end(), tag) != game_object_tags_.end();
}

bool game_object::has_tag(const char* tag) {
	if (!tag) return false;
	return has_tag(std::string(tag));
}

void game_object::add_tag(const char* tag) {
	if (!tag) return;
	if (!has_tag(tag)) {
		game_object_tags_.push_back(tag);
	}
}

void game_object::remove_tag(const char* tag)
{
	if (!tag) return;
	auto it = std::find_if(game_object_tags_.begin(), game_object_tags_.end(),
		[tag](const std::string& str) { return std::strcmp(tag, str.c_str()) == 0; });
	
	if (it != game_object_tags_.end()) {
		game_object_tags_.erase(it);
	}
}

void game_object::remove_tag(const std::string& tag)
{
	remove_tag(tag.c_str());
}

void game_object::set_pending_destroy()
{
	pending_destroy_ = true;
	for (auto cpt : components_) {
		cpt->set_pending_deletion();
	}
}

bool game_object::is_pending_destroy()
{
	if (!this) {
		throw 505;
		return true;
	}
	return pending_destroy_;
}
