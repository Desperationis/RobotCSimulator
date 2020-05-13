#pragma once
#include "Components/Components.h"
#include "Managers/SystemManager.h"
#include "Managers/ComponentManager.h"
#include "Managers/EntityManager.h"


/*
	A Entity Component System inspired by Austin Morlan's blog post.
	Austin Morlan's ECS blog post: https://austinmorlan.com/posts/entity_component_system/
*/
class ECS {
public:
	ECS() {
		componentManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();
	}

	// Entity methods

	Entity createEntity() {
		return entityManager->createEntity();
	}

	void destroyEntity(Entity entity) {
		// invalidates entity and its data
		entityManager->destroyEntity(entity);
		componentManager->entityDestroyed(entity);
		systemManager->entityDestroyed(entity);
	}


	// Component methods

	template<typename T>
	void registerComponent() {
		// required for every component introduced
		componentManager->registerComponent<T>();
	}

	template<typename T>
	void addComponent(Entity entity, T component) {
		componentManager->addComponent<T>(entity, component);

		// adds the corresponding signature to the entity
		auto signature = entityManager->getSignature(entity);
		signature.set(componentManager->getComponentType<T>(), true);
		entityManager->setSignature(entity, signature);

		// changes what systems can update it
		systemManager->entitySignatureChanged(entity, signature);
	}

	template<typename T>
	void removeComponent(Entity entity) {
		componentManager->removeComponent<T>(entity);

		// removes the corresponding signature from the entity
		auto signature = entityManager->getSignature(entity);
		signature.set(componentManager->getComponentType<T>(), false);
		entityManager->setSignature(entity, signature);

		// changes what systems update it
		systemManager->entitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& getComponent(Entity entity) {
		return componentManager->getComponent<T>(entity);
	}

	template<typename T>
	ComponentType getComponentType() {
		// returns a integer representing the bits shifted to create a unique bit mask
		return componentManager->getComponentType<T>();
	}

	ComponentType getComponentType(std::string component) {
		// returns a integer representing the bits shifted to create a unique bit mask
		return componentManager->getComponentType(component);
	}


	// System methods

	template<typename T, class... Args>
	void registerSystem(Args&&... args) {
		// required for every new system introduced
		systemManager->registerSystem<T>(args...);
	}

	template<typename T>
	void setSystemSignature(Signature signature) {
		// the signature a entity must have to get the logic of that system
		systemManager->setSignature<T>(signature);
	}

	void setSystemSignature(std::string system, Signature signature) {
		// the signature a entity must have to get the logic of that system
		systemManager->setSignature(system, signature);
	}

	void updateSystems(std::shared_ptr<ECS> ecs) {
		systemManager->updateSystems(ecs);
	}

private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;
};