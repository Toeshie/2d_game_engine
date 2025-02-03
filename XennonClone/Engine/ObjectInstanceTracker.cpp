#include "ObjectInstanceTracker.h"
#include <vector>
#include "Component.h"
#include "GameObject.h"

namespace {
	std::vector<game_object*> objects;
	std::vector<Component*> comps;
}

int ObjectInstanceTracker::component_count_ = 0;
int ObjectInstanceTracker::object_count_ = 0;

void ObjectInstanceTracker::add_object_count(game_object* other) noexcept
{
	if (!other) return;
	objects.push_back(other);
	++object_count_;
}

void ObjectInstanceTracker::remove_object_count(game_object* other) noexcept
{
	if (!other) return;
	
	auto it = std::find(objects.begin(), objects.end(), other);
	if (it != objects.end()) {
		objects.erase(it);
		--object_count_;
	}
}

void ObjectInstanceTracker::add_component_count(Component* other) noexcept
{
	if (!other) return;
	comps.push_back(other);
	++component_count_;
}

void ObjectInstanceTracker::remove_component_count(Component* other) noexcept
{
	if (!other) return;
	
	auto it = std::find(comps.begin(), comps.end(), other);
	if (it != comps.end()) {
		comps.erase(it);
		--component_count_;
	}
}

