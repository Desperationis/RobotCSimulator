#pragma once
#include <SFML/Graphics.hpp>
#include <deltaClock.h>
#include <memory>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"

/*
	Moves entities.
*/

class MovementSystem : public System {
public:
	void update(std::shared_ptr<ECS> ecs) override {
		float delta = DeltaClock::getDelta();

		for (auto const& entity : entities) {
			auto& velocity = ecs->getComponent<MovementComponent>(entity).velocity;
			auto& acceleration = ecs->getComponent<MovementComponent>(entity).acceleration;
			auto& angularSpeed = ecs->getComponent<MovementComponent>(entity).angularSpeed;
			auto& angle = ecs->getComponent<PositionComponent>(entity).angle;
			auto& position = ecs->getComponent<PositionComponent>(entity).pos;
			auto& pastPosition = ecs->getComponent<PositionComponent>(entity).pastPos;

			pastPosition = position;

			// velocity = pixels moved per second
			velocity.x += acceleration.x * delta;
			velocity.y += acceleration.y * delta;

			position.x += velocity.x * delta;
			position.y += velocity.y * delta;

			angle += angularSpeed;
		}
	};
};
