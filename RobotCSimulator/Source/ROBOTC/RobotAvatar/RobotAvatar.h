#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../ROBOTCtoC++/RobotC.h"

#define M_PI 3.1415

/*
 * RobotAvatar.h
 *
 * A little robot on screen that reacts to the motor value!
 * This class just draws the robot on screen.
 */

struct RobotAvatar : public sf::Drawable {
	sf::CircleShape trajectory;
	sf::RectangleShape rect;
	sf::Texture texture;

	sf::Vector2f position;
	sf::Vector2f velocity;
	float angle = 0;

	RobotAvatar() {
		texture.loadFromFile("Assets\\test.jpg");

		rect.setTexture(&texture);
		rect.setSize(sf::Vector2f(40, 40));

		trajectory.setOutlineColor(sf::Color::Red);
		trajectory.setFillColor(sf::Color::Transparent);
		trajectory.setOutlineThickness(3);

		position.x = 900;
		position.y = 700;
		velocity.x = 0;
		velocity.y = 0;

		sf::Vector2f newOrigin;
		newOrigin.x = rect.getLocalBounds().width / 2;
		newOrigin.y = rect.getLocalBounds().height / 2;

		rect.setOrigin(newOrigin);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform.translate(position);
		//states.transform.rotate(angle);

		target.draw(trajectory);
		target.draw(rect, states);

	}

	void Update() {
		// Manually set up left and right motor ports.
		MotorPort leftMotorPort = port1;
		MotorPort rightMotorPort = port2;
		int leftMotor = motor[leftMotorPort];
		int rightMotor = motor[rightMotorPort];
		float turnSpeed = 2;



		float speed = turnSpeed * (abs(leftMotor - rightMotor) / 254.0f);
		if (leftMotor > rightMotor) {
			angle += speed;
		}
		else if (leftMotor < rightMotor) {
			angle -= speed;
		}
	}

};