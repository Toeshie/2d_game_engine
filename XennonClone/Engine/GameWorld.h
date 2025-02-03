#pragma once

#include <string>
#include <vector>
#include "ObjectInstanceTracker.h"

class GameEngine;
class game_object;

class game_world 
{
public:
	void init(GameEngine* my_engine);

	static game_world* get_world() { return world_; }

	virtual void start() {}
	virtual void update(float deltaTime) {}

	template <typename T, typename... TArgs> 
	static T* instantiate_object(TArgs&&... mArgs) {
		T* new_object = new T(std::forward<TArgs>(mArgs)...);
		if (auto* game_obj = static_cast<game_object*>(new_object))
		{
			game_world::add_object_to_engine(game_obj);
			game_obj->start();
			return new_object;
		}
		delete new_object;  // Clean up if cast fails
		return nullptr;
	}

	static void destroy_object(game_object* Object);

	static game_object* find_object_with_tag(std::string tag);
	static std::vector<game_object*> find_all_objects_with_tag(std::string tag);

	template <typename T>
	static std::vector<T*> find_all_objects_of_type() {
		std::vector<game_object*> objs = get_all_engine_objects();
		std::vector<T*> objsC;
		objsC.reserve(objs.size());  // Pre-allocate for better performance
		
		for (auto* obj : objs) {
			if (T* casted = dynamic_cast<T*>(obj)) {
				objsC.push_back(casted);
			}
		}
		return objsC;
	}

	template <typename T>
	static T* find_object_of_type() {
		std::vector<game_object*> objs = get_all_engine_objects();
		for (auto* obj : objs) {
			if (T* casted = dynamic_cast<T*>(obj)) {
				return casted;
			}
		}
		return nullptr;
	}

protected:
	std::vector<game_object*> get_all_engine_objects();

	static game_world* world_;
	static GameEngine* engine_;

private:
	static void add_object_to_engine(game_object* obj);
};