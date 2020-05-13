#pragma once
#include <SFML/Graphics.hpp>
#include <Input/MouseInput.h>
#include <memory>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"

/*
	Moves entities according to input.
*/

class InputSystem : public System {
public:

	void update(std::shared_ptr<ECS> ecs) {
		sf::Joystick::update();

		for (auto const& entity : entities) {
			auto& position = ecs->getComponent<PositionComponent>(entity).pos;
			auto& movement = ecs->getComponent<MovementComponent>(entity);
			auto& angle = ecs->getComponent<PositionComponent>(entity).angle;
			float delta = DeltaClock::getDelta();


			if (sf::Joystick::isConnected(0)) {
				movement.acceleration.x = 0;
				movement.acceleration.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) * 20;

				if (sf::Joystick::isButtonPressed(0, 1)) {
					movement.velocity.y = -2000;
				}
			}
			else {
				movement.acceleration.x = 0;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					movement.acceleration.x = -2000;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					movement.acceleration.x = 2000;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					movement.velocity.y = -2000;
				}
			}
		}
	};
};
