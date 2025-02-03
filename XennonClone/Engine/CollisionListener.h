#pragma once

#include "box2d\b2_world_callbacks.h"
#include "MulticastDelegate.h"
#include "GameObject.h"
#include <vector>

class CollisionListener : public b2ContactListener {

private:

	struct DelegateParamStruct {

		DelegateParamStruct(game_object* Noriginal, MulticastDelegate<game_object*>* Deleg, game_object* paramM) :
			original(Noriginal),
			del(Deleg),
			param(paramM)
		{}

		game_object* original;
		MulticastDelegate<game_object*>* del;
		game_object* param;
	};

	std::vector<DelegateParamStruct> delegateList;

	bool is_valid_object(game_object* objA, game_object* ObjB);
	bool is_valid_component(class CollisionComponent* compA, CollisionComponent* compB);

public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

	void execute_handles();
	void add_delegate(game_object* caller, MulticastDelegate<game_object*>* newDelelegate, game_object* parameter);
};