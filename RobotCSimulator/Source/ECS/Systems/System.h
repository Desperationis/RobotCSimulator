#pragma once
#include "../Namespaces.h"
#include <set>
#include <memory>


/*
	A base class used to make systems generic.
*/
class ECS;
class System {
public:
	std::set<Entity> entities;
	virtual void update(std::shared_ptr<ECS> ecs) = 0;
};