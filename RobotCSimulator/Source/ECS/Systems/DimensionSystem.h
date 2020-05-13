#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include <memory>

/*
	Gives entity width and height.
*/

class DimensionSystem : public System {
public:
	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);
			auto& info = ecs->getComponent<InfoComponent>(entity);

			if (!drawable.isMeasured && drawable.drawable) {
				drawable.isMeasured = true;

				if (info.drawableType == "Shape") {
					auto shape = std::dynamic_pointer_cast<sf::Shape>(drawable.drawable);
					drawable.dimension.x = static_cast<int>(shape->getLocalBounds().width);
					drawable.dimension.y = static_cast<int>(shape->getLocalBounds().height);
				}
				else if (info.drawableType == "Sprite") {
					auto sprite = std::dynamic_pointer_cast<sf::Sprite>(drawable.drawable);
					drawable.dimension.x = static_cast<int>(sprite->getLocalBounds().width);
					drawable.dimension.y = static_cast<int>(sprite->getLocalBounds().height);
				}
			}
		}
	};
};
