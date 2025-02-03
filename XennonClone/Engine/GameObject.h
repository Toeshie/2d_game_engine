#pragma once
#include <vector>
#include <memory>
#include <array>
#include <string>

#include "ObjectInstanceTracker.h"
#include "Transform.h"

class game_world;

class game_object
{
public:
	game_object();
	game_object(Transform transform);
	game_object(Vector2D position, Vector2D scale);
	virtual ~game_object();

	virtual void start();
	virtual void update(float deltaTime) {}
	virtual void on_destroyed() {}
	virtual void on_became_visible() {}
	virtual void on_became_hidden() {}

	Transform transform;

protected:
	std::vector<std::shared_ptr<class Component>> components_;
	std::array<class Component*, 32> components_hash_map_{};  // initialize array

	std::vector<std::string> game_object_tags_;

	bool was_initialized_{false};
	bool pending_destroy_{false};
	bool is_enabled_{true};

public:
	// Component System
	using component_id = std::size_t;

	static component_id get_component_id()
	{
		static component_id last_component_id = 0;
		return last_component_id++;
	}

	template <typename T> 
	static component_id get_component_id() noexcept
	{
		static component_id type_id = get_component_id();
		return type_id;
	}

	template <typename T, typename... TArgs> 
	T* add_component(TArgs&&... mArgs)
	{
		T* new_component = new T(std::forward<TArgs>(mArgs)...);
		if (!new_component) return nullptr;

		new_component->set_owner_game_object(this);

		std::shared_ptr<Component> componentPtr{new_component};
		components_.emplace_back(std::move(componentPtr));

		component_id id = get_component_id<T>();
		if (id < components_hash_map_.size()) {
			components_hash_map_[id] = new_component;
		}

		new_component->start();
		ObjectInstanceTracker::add_component_count(new_component);

		return new_component;
	}

	template <typename T> 
	T* get_component()
	{
		component_id id = get_component_id<T>();
		if (id >= components_hash_map_.size()) return nullptr;
		
		auto component_found = components_hash_map_[id];
		return static_cast<T*>(component_found);
	}

	// Getters and Setters
	inline std::vector<std::shared_ptr<Component>> get_all_components() const { return components_; }
	inline bool get_was_initialized() const { return was_initialized_; }
	inline Transform* get_transform() { return &transform; }
	inline bool get_is_enabled() const { return is_enabled_; }
	inline void set_enabled(bool enabled) { is_enabled_ = enabled; }

	// Tag System
	bool has_tag(const std::string& tag);
	bool has_tag(const char* tag);
	void add_tag(const char* tag);
	void remove_tag(const char* tag);
	void remove_tag(const std::string& tag);
	std::vector<std::string> get_tags() const { return game_object_tags_; }

	// State Management
	void set_pending_destroy();
	bool is_pending_destroy();
};

