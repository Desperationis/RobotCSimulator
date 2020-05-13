#include "Factory.h"
#include "ECS.h"
#include "Components/Components.h"
#include <Debug/Log.h>
#include <Debug/Debug.h>

Factory::Factory(std::shared_ptr<ECS> ecs, const char* entityBlueprint) {
	this->ecs = ecs;
	XML::loadXML(&document, &fileData, entityBlueprint);
}

std::string Factory::formatError(std::string item, std::string listName) {
	std::string error = "\"" + item + "\"" + " is not defined in the deserialization of " + listName + ".";
	return error;
}

Entity Factory::loadEntity(std::string entityType) {
	xml_node<>* blueprint = XML::getFirstNode(document, "Entities");

	for (xml_node<>* entityBlueprint = blueprint->first_node(); entityBlueprint; entityBlueprint = entityBlueprint->next_sibling()) {
		std::string entityName = XML::getAttribute(entityBlueprint, "name");

		if (entityName == entityType) {
			Entity entity = ecs->createEntity();

			InfoComponent info;
			ecs->addComponent(entity, info);

			for (xml_node<>* component = entityBlueprint->first_node(); component; component = component->next_sibling()) {
				std::string componentName = XML::getName(component);
				deserializeComponent(entity, component, componentName);
			}

			return entity;
		}
	}

	Log::descriptionLog(formatError(entityType, "Entities"));
	return -1;
}


void Factory::deserializeComponent(Entity entity, xml_node<>* component, std::string componentName) {
	if (componentName == "Input") ecs->addComponent(entity, InputComponent{});
	else if (componentName == "Debug") ecs->addComponent(entity, DebugComponent{});
	else if (componentName == "Loop") ecs->addComponent(entity, LoopComponent{});
	else if (componentName == "Drawable") deserializeDrawable(entity, component);
	else if (componentName == "Collision") deserializeCollision(entity, component);

	else if (componentName == "Position") {
		PositionComponent position;
		XML::linkValues(position.pos.x, XML::getAttribute(component, "X"));
		XML::linkValues(position.pos.y, XML::getAttribute(component, "Y"));
		XML::linkValues(position.angle, XML::getAttribute(component, "Angle"));

		ecs->addComponent(entity, position);
	}
	else if (componentName == "Movement") {
		MovementComponent movement;
		XML::linkValues(movement.velocity.x, XML::getAttribute(component, "VelocityX"));
		XML::linkValues(movement.velocity.y, XML::getAttribute(component, "VelocityY"));
		XML::linkValues(movement.acceleration.x, XML::getAttribute(component, "AccelerationX"));
		XML::linkValues(movement.acceleration.y, XML::getAttribute(component, "AccelerationY"));
		XML::linkValues(movement.angularSpeed, XML::getAttribute(component, "AngularSpeed"));

		ecs->addComponent(entity, movement);
	}
	else {
		Log::descriptionLog(formatError(componentName, "component"));
	}
}

void Factory::deserializeDrawable(Entity entity, xml_node<>* component) {
	DrawableComponent drawable;
	auto& info = ecs->getComponent<InfoComponent>(entity);

	for (xml_node<>* subComponent = component->first_node(); subComponent; subComponent = subComponent->next_sibling()) {
		if (XML::getName(subComponent) == "Texture") {
			TextureComponent texture;
			texture.fileName = XML::getAttribute(subComponent, "file");

			ecs->addComponent(entity, texture);
		}
		else if (XML::getName(subComponent) == "Color") {
			ColorComponent colorComponent;
			sf::Color colorRaw;

			XML::linkValues(colorRaw.r, XML::getAttribute(subComponent, "R"));
			XML::linkValues(colorRaw.g, XML::getAttribute(subComponent, "G"));
			XML::linkValues(colorRaw.b, XML::getAttribute(subComponent, "B"));
			XML::linkValues(colorRaw.a, XML::getAttribute(subComponent, "A"));

			colorComponent.setColor(colorRaw);
			ecs->addComponent(entity, colorComponent);
		}
		else if (XML::getName(subComponent) == "Circle") {
			info.drawableType = "Shape";
			drawable.drawable = std::make_shared<sf::CircleShape>();
			auto circle = std::dynamic_pointer_cast<sf::CircleShape>(drawable.drawable);


			circle->setRadius(XML::getValue<float>(XML::getAttribute(subComponent, "Radius")));
		}
		else if (XML::getName(subComponent) == "Rectangle") {
			info.drawableType = "Shape";
			drawable.drawable = std::make_shared<sf::RectangleShape>();
			auto rectangle = std::dynamic_pointer_cast<sf::RectangleShape>(drawable.drawable);

			sf::Vector2f size;

			XML::linkValues(size.x, XML::getAttribute(subComponent, "Width"));
			XML::linkValues(size.y, XML::getAttribute(subComponent, "Height"));

			rectangle->setSize(size);
		}
		else if (XML::getName(subComponent) == "Sprite") {
			info.drawableType = "Sprite";
			drawable.drawable = std::make_shared<sf::Sprite>();
		}
		else {
			Log::descriptionLog(formatError(XML::getName(subComponent), "Drawable"));
		}
	}

	ecs->addComponent(entity, drawable);
}

void Factory::deserializeCollision(Entity entity, xml_node<>* component) {
	CollisionComponent collision;
	collision.event = std::make_shared<CollisionEvent>();

	for (xml_node<>* subComponent = component->first_node(); subComponent; subComponent = subComponent->next_sibling()) {
		if (XML::getName(subComponent) == "WallCollision") {
			ecs->addComponent(entity, WallCollisionComponent{});
		}
		else if (XML::getName(subComponent) == "RenderCollision") {
			RenderCollisionComponent renderCollision;

			renderCollision.hitBoxRender.setPrimitiveType(sf::Lines);
			renderCollision.hitBoxRender.resize(8);

			ecs->addComponent(entity, renderCollision);
		}
		else {
			Log::descriptionLog(formatError(XML::getName(subComponent), "Collision"));
		}
	}

	ecs->addComponent(entity, collision);
}