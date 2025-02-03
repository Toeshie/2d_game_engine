#include "GameWorld.h"
#include "GameObject.h"
#include "GameEngine.h"

float triangleArea(Vector2D A, Vector2D B, Vector2D C);
bool isInsideSquare(Vector2D A, Vector2D B, Vector2D C, Vector2D D, Vector2D P);

game_world* game_world::world_ = nullptr;
GameEngine* game_world::engine_ = nullptr;

void game_world::add_object_to_engine(game_object* obj)
{
	if (obj) {
		GameEngine::add_game_object(obj);
	}
}

void game_world::init(GameEngine* my_engine)
{
	if (world_) {
		delete this;
	}
	else {
		engine_ = my_engine;
		world_ = this;
	}
}

void game_world::destroy_object(game_object* Object)
{
	if (Object && engine_) {
		Object->set_pending_destroy();
		engine_->add_pending_destroy(Object);
	}
}

game_object* game_world::find_object_with_tag(std::string tag)
{
	if (!engine_) return nullptr;
	
	std::vector<game_object*> objs = engine_->get_all_game_objects();
	for (auto* obj : objs) {
		if (obj && obj->has_tag(tag)) {
			return obj;
		}
	}
	return nullptr;
}

std::vector<game_object*> game_world::find_all_objects_with_tag(std::string tag)
{
	std::vector<game_object*> withTag;
	if (engine_) {	
		std::vector<game_object*> objs = engine_->get_all_game_objects();
		withTag.reserve(objs.size());  // Pre-allocate for better performance
		
		for (auto* obj : objs) {
			if (obj && obj->has_tag(tag)) {
				withTag.push_back(obj);
			}
		}
	}
	return withTag;
}

std::vector<game_object*> game_world::get_all_engine_objects()
{
	return engine_ ? engine_->get_all_game_objects() : std::vector<game_object*>();
}
