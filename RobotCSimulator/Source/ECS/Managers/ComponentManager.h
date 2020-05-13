#pragma once
#include "../Namespaces.h"
#include <Debug/Debug.h>
#include <Data/packed_array.hpp>
#include "tsl/hopscotch_map.h"
#include <memory>
#include <iostream>


/*
	Stores component arrays and manages their data.
*/
class ComponentManager {
public:
	template<class T>
	std::string formatTypeName() {
		std::string typeName = typeid(T).name();

		// all components are structures, so we erase "struct " from typeName
		typeName.erase(typeName.begin(), typeName.begin() + 7);

		return typeName;
	}

	template<class T>
	void registerComponent() {
		std::string typeName = formatTypeName<T>();

		std::string error = "\"" + typeName + "\"" + " has been registered more than once as a component.";
		Log::assertionLog(error, componentTypes.find(typeName) == componentTypes.end());

		// register the component's type and create a array for it
		componentTypes[typeName] = nextComponentType;
		componentArrays[typeName] = std::make_shared<packed_array<T, MAX_ENTITIES>>();
		nextComponentType++;
	}

	template<class T>
	ComponentType getComponentType() {
		std::string typeName = formatTypeName<T>();

		std::string error = "\"" + typeName + "\"" + " does not exist as a registered component.";
		Log::assertionLog(error, componentTypes.find(typeName) != componentTypes.end());

		// return this component's type - used for creating signatures
		return componentTypes[typeName];
	}


	ComponentType getComponentType(std::string component) {
		std::string typeName = component;

		std::string error = "\"" + typeName + "\"" + " does not exist as a registered component.";

		Log::assertionLog(error, componentTypes.find(typeName) != componentTypes.end());

		// return this component's type - used for creating signatures
		return componentTypes[typeName];
	}

	template <typename B, typename T>
	const B* is_unambiguous_public_base_of(const T* obj) {
		try {
			throw obj;
		}
		catch (const B* pb) {
			return pb;
		}
		catch (...) {
		}
		return nullptr;
	}

	template<class T>
	void addComponent(Entity entity, T component) {
		std::string error = "\"" + formatTypeName<T>() + "\"" + " cannot be added as it is not registered as a component.";
		Log::assertionLog(error, is_unambiguous_public_base_of<Component, T>(&component));
		getComponentArray<T>()->insert(entity, component);
	}

	template<class T>
	void removeComponent(Entity entity) {
		getComponentArray<T>()->erase(entity);
	}

	template<class T>
	T& getComponent(Entity entity) {
		return getComponentArray<T>()->get(entity);
	}

	void entityDestroyed(Entity entity) {
		for (auto const& pair : componentArrays) {
			auto const& componentArray = pair.second;

			componentArray->erase(entity);
		}
	}


private:
	tsl::hopscotch_map<std::string, ComponentType> componentTypes{};
	tsl::hopscotch_map<std::string, std::shared_ptr<Ipacked_array>> componentArrays{};

	// increments for each new unique component
	ComponentType nextComponentType{};

	template<class T>
	std::shared_ptr<packed_array<T, MAX_ENTITIES>> getComponentArray() {
		std::string typeName = typeid(T).name();
		typeName.erase(typeName.begin(), typeName.begin() + 7);
		return std::static_pointer_cast<packed_array<T, MAX_ENTITIES>>(componentArrays[typeName]);
	}
};