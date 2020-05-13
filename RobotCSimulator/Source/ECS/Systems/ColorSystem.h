#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include <memory>

/*
	Colors entities.
*/

class ColorSystem : public System {
public:
	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& color = ecs->getComponent<ColorComponent>(entity);
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);
			auto& info = ecs->getComponent<InfoComponent>(entity);

			if (!color.isApplied) {
				if (info.drawableType == "Shape") {
					auto shape = std::dynamic_pointer_cast<sf::Shape>(drawable.drawable);
					shape->setFillColor(color.color);
				}
				else if (info.drawableType == "Sprite") {
					auto sprite = std::dynamic_pointer_cast<sf::Sprite>(drawable.drawable);
					sprite->setColor(color.color);
				}

				color.isApplied = true;
			}
		}
	};
};
