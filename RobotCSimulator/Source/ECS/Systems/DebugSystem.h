#pragma once
#include <SFML/Graphics.hpp>
#include <Debug/Debug.h>
#include <memory>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"

/*
	Displays an entitie's info.
*/

class DebugSystem : public System {
public:
	template<class T>
	std::string toStr(T arg) {
		std::stringstream buf;
		buf << arg;

		return buf.str();
	}

	template<typename T>
	void toText(std::string label, T value) {
		std::string form = label + toStr(value);
		ImGui::Text(form.c_str());
	}

	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& position = ecs->getComponent<PositionComponent>(entity);
			auto& movement = ecs->getComponent<MovementComponent>(entity);
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);
			auto& info = ecs->getComponent<InfoComponent>(entity);
			auto& color = ecs->getComponent<ColorComponent>(entity);

			std::string format = "Debug Info on Entity " + toStr(entity);

			ImGui::Begin(format.c_str());
			
			toText("Position X: ", position.pos.x);
			toText("Position Y: ", position.pos.y);
			toText("Angle: ", position.angle);
			toText("Velocity X: ", movement.velocity.x);
			toText("Velocity Y: ", movement.velocity.y);
			toText("Acceleration X: ", movement.acceleration.x);
			toText("Acceleration Y: ", movement.acceleration.y);
			toText("Drawable Width: ", drawable.getDimension().x);
			toText("Drawable Height: ", drawable.getDimension().y);
			toText("Drawable Type: ", info.drawableType);
			toText("FPS: ", Debug::getFps());

			float bufColor[4] = { color.getColor().r / 255.0f,
								  color.getColor().g / 255.0f,
								  color.getColor().b / 255.0f,
								  color.getColor().a / 255.0f};

			ImGui::ColorPicker4("Color", bufColor);
			sf::Color sfBufColor;
			sfBufColor.r = bufColor[0] * 255;
			sfBufColor.g = bufColor[1] * 255;
			sfBufColor.b = bufColor[2] * 255;
			sfBufColor.a = bufColor[3] * 255;
			color.setColor(sfBufColor);


			ImGui::End();

		}
	};
};
