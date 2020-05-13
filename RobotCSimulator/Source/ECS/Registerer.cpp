#include "Registerer.h"
#include "ECS.h"
#include <Debug/Log.h>
#include "Components/Components.h"
#include "Systems/DrawableSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/TextureSystem.h"
#include "Systems/DebugSystem.h"
#include "Systems/DimensionSystem.h"
#include "Systems/ColorSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/WallCollisionSystem.h"
#include "Systems/CollisionRenderSystem.h"
#include "Systems/LoopSystem.h"

Registerer::Registerer(std::shared_ptr<ECS> ecs, std::shared_ptr<sf::RenderWindow> window, const char* systemBlueprint) {
	this->ecs = ecs;

	registerComponents();
	registerSystems(window);

	XML::loadXML(&document,&fileData, systemBlueprint);
	loadSystemSignatures();
}

Registerer::~Registerer() {
	delete document;
	document = nullptr;

	delete fileData;
	fileData = nullptr;
}


void Registerer::loadSystemSignatures() {
	xml_node<>* parent = XML::getFirstNode(document, "Systems");

	for (xml_node<>* system = parent->first_node(); system; system = system->next_sibling()) {
		Signature signature;

		for (xml_node<>* component = system->first_node(); component; component = component->next_sibling()) {
			std::string name = XML::getName(component);
			name += "Component";
			signature.set(ecs->getComponentType(name));
		}

		std::string systemName = system->first_attribute()->value();
		std::string attributeName = system->first_attribute()->name();
		if (attributeName != "name") {
			std::string error = systemName + " doesn't use \"name\" as an attribute.";
			Log::descriptionLog(error);
		}

		ecs->setSystemSignature(systemName, signature);
	}
}

void Registerer::registerSystems(std::shared_ptr<sf::RenderWindow> window) {
	// update order sensitive
	ecs->registerSystem<InputSystem>();
	ecs->registerSystem<MovementSystem>();
	ecs->registerSystem<LoopSystem>();
	ecs->registerSystem<CollisionSystem>(window);
	ecs->registerSystem<WallCollisionSystem>(window);
	ecs->registerSystem<TextureSystem>();
	ecs->registerSystem<ColorSystem>();
	ecs->registerSystem<DebugSystem>();
	ecs->registerSystem<DimensionSystem>();
	ecs->registerSystem<DrawableSystem>(window);
	ecs->registerSystem<CollisionRenderSystem>(window);
}

void Registerer::registerComponents() {
	// not order sensitive, at all
	ecs->registerComponent<DrawableComponent>();
	ecs->registerComponent<LoopComponent>();
	ecs->registerComponent<PositionComponent>();
	ecs->registerComponent<InputComponent>();
	ecs->registerComponent<TextureComponent>();
	ecs->registerComponent<MovementComponent>();
	ecs->registerComponent<ColorComponent>();
	ecs->registerComponent<DebugComponent>();
	ecs->registerComponent<CollisionComponent>();
	ecs->registerComponent<WallCollisionComponent>();
	ecs->registerComponent<InfoComponent>();
	ecs->registerComponent<RenderCollisionComponent>();
}