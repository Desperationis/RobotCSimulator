#pragma once
#include "Namespaces.h"
#include <Data/XML.h>
#include <memory>


/*
	Assembles different types of entities based off XML blueprints.
*/

class ECS;
class Factory {
public:
	Factory(std::shared_ptr<ECS> ecs, const char* entityBlueprint);
	Entity loadEntity(std::string entityType);

private:
	std::shared_ptr<ECS> ecs;
	xml_document<>* document;
	file<>* fileData;

private:
	std::string formatError(std::string item, std::string listName);

	void deserializeComponent(Entity entity, xml_node<>* component, std::string componentName);
	void deserializeDrawable(Entity entity, xml_node<>* component);
	void deserializeCollision(Entity entity, xml_node<>* component);
};