#include "CollisionListener.h"
#include "box2d\b2_contact.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "GameEngine.h"
#include <mutex>
#include "GameObject.h"

bool CollisionListener::is_valid_object(game_object* objA, game_object* objB)
{
	if (objA == nullptr || objB == nullptr) {
		return false;
	}
	return !objA->is_pending_destroy() && !objB->is_pending_destroy();
}

bool CollisionListener::is_valid_component(CollisionComponent* compA, CollisionComponent* compB)
{
	if (!compA || !compB)
	{
		return false;
	}
	if (compA->get_marked_for_deletion() || compB->get_marked_for_deletion())return false;
	return compA->get_is_collision_enabled() && compB->get_is_collision_enabled();
}

void CollisionListener::BeginContact(b2Contact* contact)
{
	auto compA = reinterpret_cast<CollisionComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	auto compB = reinterpret_cast<CollisionComponent*>(contact->GetFixtureB()->GetUserData().pointer);
	
	if (!is_valid_component(compA, compB)) {
		return;
	}

	game_object* objA = compA->get_owner_game_object();
	game_object* objB = compB->get_owner_game_object();

	if (!is_valid_object(objA, objB)) {
		return;
	}

	if (compA->get_is_trigger() || compB->get_is_trigger()) {

		add_delegate(objA, &compA->on_trigger_enter, objB);
		add_delegate(objB, &compB->on_trigger_enter, objA);
	
	}
	else {
		
		add_delegate(objA, &compA->on_collision_enter, objB);
		add_delegate(objB, &compB->on_collision_enter, objA);
	
	}
}

void CollisionListener::EndContact(b2Contact* contact) 
{
	auto compA = reinterpret_cast<CollisionComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	auto compB = reinterpret_cast<CollisionComponent*>(contact->GetFixtureB()->GetUserData().pointer);
	if (!is_valid_component(compA, compB)) {
		return;
	}
	game_object* objA = compA->get_owner_game_object();
	game_object* objB = compB->get_owner_game_object();

	if (!is_valid_object(objA, objB)) {
		return;
	}

	if (compA->get_is_trigger() || compB->get_is_trigger()) {
		
		add_delegate(objA, &compA->on_trigger_exit, objB);
		add_delegate(objB, &compB->on_trigger_exit, objA);
		
	}
	else {

		add_delegate(objA, &compA->on_collision_exit, objB);
		add_delegate(objB, &compB->on_collision_exit, objA);
		
	}
}


static std::mutex m_HandlesMutex;
void CollisionListener::execute_handles()
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);
	if (delegateList.empty()) {
		return;
	}

	for (const auto& delegate : delegateList) {
		delegate.del->Broadcast(delegate.param);
	}
	delegateList.clear();
}

void CollisionListener::add_delegate(game_object* caller, MulticastDelegate<game_object*>* newDel, game_object* param)
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);

	for (const auto& delegate : delegateList) {
		if (delegate.original == caller && delegate.del == newDel && delegate.param == param) {
			return;
		}
	}
	delegateList.emplace_back(caller, newDel, param);
}

