#pragma once

// Forward declarations
class game_object;
class Component;

class ObjectInstanceTracker
{
	static int component_count_;
	static int object_count_;

public:
	ObjectInstanceTracker() = delete;
	ObjectInstanceTracker(const ObjectInstanceTracker&) = delete;
	ObjectInstanceTracker& operator=(const ObjectInstanceTracker&) = delete;

	//noexcept since these operations shouldn't throw
	static void add_object_count(game_object* other) noexcept;
	static void remove_object_count(game_object* other) noexcept;
	static void add_component_count(Component* other) noexcept;
	static void remove_component_count(Component* other) noexcept;

	//constexpr for compile-time optimization
	static constexpr int get_component_count() noexcept { return component_count_; }
	static constexpr int get_object_count() noexcept { return object_count_; }

};

