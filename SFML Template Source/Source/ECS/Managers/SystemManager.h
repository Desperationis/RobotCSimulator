#pragma once
#include "../Namespaces.h"
#include "../Systems/System.h"
#include <Debug/Log.h>
#include "tsl/hopscotch_map.h"
#include <memory>

/*
	Notifies all systems when an entity has changed signature or has been destroyed. 
*/
class SystemManager {
public:
	template<class T>
	std::string formatTypeName() {
		std::string typeName = typeid(T).name();

		// all systems are classes, so we erase "class " from typeName
		typeName.erase(typeName.begin(), typeName.begin() + 6);

		return typeName;
	}

	template<class T, class... Args>
	void registerSystem(Args&&... args) {
		std::string typeName = formatTypeName<T>();

		std::string error = "\"" + typeName + "\"" + " cannot be registered more than once as a registered system.";
		Log::assertionLog(error, typeToIndex.find(typeName) == typeToIndex.end());

		auto system = std::make_shared<T>(args...);
		typeToIndex[typeName] = size;
		size++;
		systems.push_back(system);
	}

	void setSignature(std::string system, Signature signature) {
		std::string error = "\"" + system + "\"" + " does not exist as a registered system.";
		Log::assertionLog(error, typeToIndex.find(system) != typeToIndex.end());

		signatures[system] = signature;
	}

	void entityDestroyed(Entity entity) {
		for (auto const& system : systems){
			system->entities.erase(entity);
		}
	}

	void entitySignatureChanged(Entity entity, Signature entitySignature) {
		for (auto const& pair : typeToIndex) {
			auto const& type = pair.first;
			auto const& system = systems[pair.second];
			auto const& systemSignature = signatures[type];

			// unordered_map won't bring up a abort() if the entity doesn't / already exist
			if ((entitySignature & systemSignature) == systemSignature && systemSignature.any()) {
				system->entities.insert(entity);
			}
			else{
				system->entities.erase(entity);
			}
		}
	}

	void updateSystems(std::shared_ptr<ECS> ecs) {
		for (auto const& system : systems) {
			system->update(ecs);
		}
	}


private:
	// holds bitmaps representing the components associated with each system
	tsl::hopscotch_map<std::string, Signature> signatures;
	tsl::hopscotch_map<std::string, size_t> typeToIndex;
	std::vector<std::shared_ptr<System>> systems;

	size_t size = 0;
};