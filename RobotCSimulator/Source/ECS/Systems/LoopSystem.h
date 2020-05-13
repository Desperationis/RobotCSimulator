#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include <memory>

/*
	"Loops" entities back to the opposite side of the screen if they get too far.
*/

class LoopSystem : public System {
public:
	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& position = ecs->getComponent<PositionComponent>(entity);
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);

			if (position.pos.x > 900) {
				position.pos.x = -drawable.getDimension().x;
			}
			else if (position.pos.x + drawable.getDimension().x < 0) {
				position.pos.x = 900;
			}

		}
	};
};
