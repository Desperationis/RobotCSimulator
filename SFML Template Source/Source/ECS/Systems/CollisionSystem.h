#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include <memory>

/*
	COOLISION
*/

class CollisionSystem : public System {
public:
	CollisionSystem(std::shared_ptr<sf::RenderWindow> window) {
		this->window = window;
	}

	template <class T>
	bool samePolarity(T a, T b) {
		return ((a > 0 && b > 0) || (a < 0 && b < 0));
	}

	bool checkCollision(CollisionComponent& collision, CollisionComponent& targetCollision) {
		return (collision.hitBox.left < targetCollision.hitBox.left + targetCollision.hitBox.width &&
			collision.hitBox.left + collision.hitBox.width > targetCollision.hitBox.left &&
			collision.hitBox.top < targetCollision.hitBox.top + targetCollision.hitBox.height &&
			collision.hitBox.top + collision.hitBox.height > targetCollision.hitBox.top);
	}

	void update(std::shared_ptr<ECS> ecs) {
		// update each hitbox's positions
		for (auto const& entity : entities) {
			auto& position = ecs->getComponent<PositionComponent>(entity);
			auto& movement = ecs->getComponent<MovementComponent>(entity);
			auto& collision = ecs->getComponent<CollisionComponent>(entity);
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);

			collision.hitBox.left = position.pos.x;
			collision.hitBox.top = position.pos.y;
			collision.hitBox.width = static_cast<float>(drawable.getDimension().x);
			collision.hitBox.height = static_cast<float>(drawable.getDimension().y);
		}

		// check for collision
		for (auto const& entity : entities) {
			auto& collision = ecs->getComponent<CollisionComponent>(entity);

			for (auto const& target : entities) {
				if (entity != target) {
					auto& targetCollision = ecs->getComponent<CollisionComponent>(target);

					if (checkCollision(collision, targetCollision)) {
						collision.event->target = target;
						collision.event->active = true;
						break;
					}

				}
			}
		}
	};

protected:
	std::shared_ptr<sf::RenderWindow> window;
};
