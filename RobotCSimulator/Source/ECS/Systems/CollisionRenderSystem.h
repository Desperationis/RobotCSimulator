#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include <memory>

/*
	Renders the collision box of an entity.
*/

class CollisionRenderSystem : public System {
public:
	CollisionRenderSystem(std::shared_ptr<sf::RenderWindow> window) {
		this->window = window;
	}

	void updateHitBoxRender(RenderCollisionComponent& renderCollision, CollisionComponent& collision) {
		renderCollision.hitBoxRender[0].position = sf::Vector2f(collision.hitBox.left, collision.hitBox.top);
		renderCollision.hitBoxRender[1].position = sf::Vector2f(collision.hitBox.left + collision.hitBox.width, collision.hitBox.top);
				 
		renderCollision.hitBoxRender[2].position = sf::Vector2f(collision.hitBox.left + collision.hitBox.width, collision.hitBox.top);
		renderCollision.hitBoxRender[3].position = sf::Vector2f(collision.hitBox.left + collision.hitBox.width, collision.hitBox.top + collision.hitBox.height);
				 
		renderCollision.hitBoxRender[4].position = sf::Vector2f(collision.hitBox.left + collision.hitBox.width, collision.hitBox.top + collision.hitBox.height);
		renderCollision.hitBoxRender[5].position = sf::Vector2f(collision.hitBox.left, collision.hitBox.top + collision.hitBox.height);

		renderCollision.hitBoxRender[6].position = sf::Vector2f(collision.hitBox.left, collision.hitBox.top + collision.hitBox.height);
		renderCollision.hitBoxRender[7].position = sf::Vector2f(collision.hitBox.left, collision.hitBox.top);

		for (int i = 0; i < 8; i++) {
			renderCollision.hitBoxRender[i].color = sf::Color::Red;
		}
	}

	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& collision = ecs->getComponent<CollisionComponent>(entity);
			auto& renderCollision = ecs->getComponent<RenderCollisionComponent>(entity);

			updateHitBoxRender(renderCollision, collision);
			window->draw(renderCollision.hitBoxRender);
		}
	};

private:
	std::shared_ptr<sf::RenderWindow> window;
};