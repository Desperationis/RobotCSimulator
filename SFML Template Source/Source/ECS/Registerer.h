#pragma once
#include <SFML/Graphics.hpp>
#include "Namespaces.h"
#include <Data/XML.h>
#include <memory>


/*
	Registers components and systems into the ECS.
*/

class ECS;
class Registerer {
public:
	Registerer(std::shared_ptr<ECS> ecs, std::shared_ptr<sf::RenderWindow> window, const char* systemBlueprint);
	~Registerer();

private:
	std::shared_ptr<ECS> ecs;
	xml_document<>* document;
	file<>* fileData;

	void loadSystemSignatures();
	void registerComponents();
	void registerSystems(std::shared_ptr<sf::RenderWindow> window);
};