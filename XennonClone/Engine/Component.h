#pragma once

class Component
{
public:
	virtual void start();
	virtual void update(float deltatime);

protected:
	class game_object* component_owner_ = nullptr;

	bool marked_for_deletion_ = false;
	bool is_active_ = true;

public:
	// Sets the owner game object for this component.
	inline void set_owner_game_object(class game_object* gameObject) { component_owner_ = gameObject; }

	// Returns whether the component is marked for deletion.
	inline bool get_marked_for_deletion() const { return marked_for_deletion_; }
	
	// Marks the component as pending deletion.
	inline void set_pending_deletion() { marked_for_deletion_ = true; }

	// Returns the owner game object.
	inline game_object* get_owner_game_object() const { return component_owner_; }

	virtual void on_destroyed() {};

	// Sets the active state of the component.
	virtual void set_active(bool bVal) { is_active_ = bVal; }

	// Returns whether the component is active.
	inline bool get_is_active() const { return is_active_; }
};

