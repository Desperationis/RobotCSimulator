#pragma once
#include "../Namespaces.h"
#include <Debug/Log.h>
#include <array>
#include <queue>
#include <iostream>

/*
	Distributes entities and signatures associated with them.
*/

struct EntityManager {
public:
	EntityManager() {
		for (size_t i = 0; i < MAX_ENTITIES; i++) {
			unusedIds.push(i);
		}
	}

	Entity createEntity() {
		Log::assertionLog("The maximum limit has been reached!", numberOfEntities < MAX_ENTITIES);

		// returns an entity off the queue
		Entity frontID = unusedIds.front();
		unusedIds.pop();
		numberOfEntities++;

		return frontID;
	}

	void destroyEntity(Entity entity) {
		Log::assertionLog("Entity out of range.", entity < MAX_ENTITIES && entity >= 0);

		// puts the entity back into the queue
		unusedIds.push(entity);

		// invalidate signature
		signatures[entity].reset();

		numberOfEntities--;
	}

	void setSignature(Entity entity, Signature signature) {
		Log::assertionLog("Entity out of range.", entity < MAX_ENTITIES && entity >= 0);

		signatures[entity] = signature;
	}

	Signature getSignature(Entity entity) {
		Log::assertionLog("Entity out of range.", entity < MAX_ENTITIES && entity >= 0);

		return signatures[entity];
	}

private:
	std::queue<Entity> unusedIds;

	// bitsets representing component flags
	std::array<Signature, MAX_ENTITIES> signatures;

	// used to prevent grabbing from a empty queue
	size_t numberOfEntities{};
};