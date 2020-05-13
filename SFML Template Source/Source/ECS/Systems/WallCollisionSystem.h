#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"
#include "CollisionSystem.h"
#include <memory>

/*
	Test class
*/

class WallCollisionSystem : public CollisionSystem {
public:
	WallCollisionSystem(std::shared_ptr<sf::RenderWindow> window) : CollisionSystem(window)  { }

	void update(std::shared_ptr<ECS> ecs) {
		for (auto const& entity : entities) {
			auto& collisionEvent = ecs->getComponent<CollisionComponent>(entity).event;
			auto& collision = ecs->getComponent<CollisionComponent>(entity);
			auto& position = ecs->getComponent<PositionComponent>(entity);
			auto& movement = ecs->getComponent<MovementComponent>(entity);


			if (collisionEvent->active) {
				auto& targetCollision = ecs->getComponent<CollisionComponent>(collisionEvent->target);
				auto& targetMovement = ecs->getComponent<MovementComponent>(collisionEvent->target);
				
				collision.hitBox.left = position.pastPos.x;
				collision.hitBox.top = position.pastPos.y;


				collision.hitBox.left = position.pos.x;
				if (checkCollision(collision, targetCollision)) {
					if (movement.velocity.x > 0) {
						position.pos.x = targetCollision.hitBox.left - collision.hitBox.width;
					}
					else if (movement.velocity.x < 0) {
						position.pos.x = targetCollision.hitBox.left + targetCollision.hitBox.width;
					}
					movement.velocity.x = 0;
				}

				collision.hitBox.left = position.pos.x;


				collision.hitBox.top = position.pos.y;
				if (checkCollision(collision, targetCollision)) {
					if (movement.velocity.y > 0) {
						position.pos.y = targetCollision.hitBox.top - collision.hitBox.height;
					}
					else if (movement.velocity.y < 0) {
						position.pos.y = targetCollision.hitBox.top + targetCollision.hitBox.height;
					}
					movement.velocity.y = 0;
				}

				collision.hitBox.top = position.pos.y;
				collisionEvent->active = false;
			}
		}
	};
};
