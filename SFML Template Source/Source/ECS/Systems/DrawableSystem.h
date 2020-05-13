#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include <memory>

/*
	Renders sf::Drawables from entities.
*/

class DrawableSystem : public System {
public:
	DrawableSystem(std::shared_ptr<sf::RenderWindow> window) {
		this->window = window;
	}
	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);
			auto& position = ecs->getComponent<PositionComponent>(entity);

			sf::RenderStates state;
			state.transform.translate(position.pos);
			state.transform.rotate(position.angle);

			if (drawable.drawable) {
				window->draw(*drawable.drawable, state);
			}
			else {
				// if it doesn't have a drawable, remove it entirely 
				ecs->removeComponent<DrawableComponent>(entity);
			}
		}
	};

private:
	std::shared_ptr<sf::RenderWindow> window;
};
