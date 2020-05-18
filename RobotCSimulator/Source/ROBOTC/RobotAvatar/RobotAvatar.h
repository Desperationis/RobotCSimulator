#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../ROBOTCtoC++/RobotC.h"

#define M_PI 3.1415

/*
 * RobotAvatar.h
 *
 * A little robot on screen that reacts to the motor value!
 */

struct RobotAvatar : public sf::Drawable {
	// Drawing variables
	sf::RectangleShape rect;
	sf::Texture texture;

	// Everything else
	enum Turn {LeftTurn, RightTurn, Still, MOVIN};
	sf::Vector2f position;
	sf::Vector2f velocity;
	float angle = 0;

	RobotAvatar() {
		// Load texture.
		texture.loadFromFile("Assets\\Clawbot.jpg");
		rect.setTexture(&texture);
		rect.setSize(sf::Vector2f(80, 80));

		// Initial position and speed.
		position.x = 900;
		position.y = 700;
		velocity.x = 0;
		velocity.y = 0;

		// Origin in center.
		sf::Vector2f newOrigin;
		newOrigin.x = rect.getLocalBounds().width / 2;
		newOrigin.y = rect.getLocalBounds().height / 2;
		rect.setOrigin(newOrigin);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform.translate(position);
		states.transform.rotate(angle);

		target.draw(rect, states);

	}

	void Update() {
		// Manually set up left and right motor ports.
		MotorPort leftMotorPort = port1;
		MotorPort rightMotorPort = port2;
		int leftMotor = motor[leftMotorPort];
		int rightMotor = motor[rightMotorPort];
		float turnSpeed = 5;
		float movementSpeed = 10;

		// Set angle based on motor's values.
		float speed = turnSpeed * (abs(leftMotor - rightMotor) / 254.0f);
		if (leftMotor > rightMotor) {
			angle += speed;
		}
		else if (leftMotor < rightMotor) {
			angle -= speed;
		}

		// Set actual speed.
		switch (GetTurn()) {
		case LeftTurn:
			velocity.x = cos(angle * (M_PI / 180.0f)) * (rightMotor / 254.0f) * movementSpeed;
			velocity.y = sin(angle * (M_PI / 180.0f)) * (rightMotor / 254.0f) * movementSpeed;
			break;
		case RightTurn:
			velocity.x = cos(angle * (M_PI / 180.0f)) * (leftMotor / 254.0f) * movementSpeed;
			velocity.y = sin(angle * (M_PI / 180.0f)) * (leftMotor / 254.0f) * movementSpeed;
			break;
		case MOVIN:
			velocity.x = cos(angle * (M_PI / 180.0f)) * (leftMotor / 254.0f) * movementSpeed;
			velocity.y = sin(angle * (M_PI / 180.0f)) * (leftMotor / 254.0f) * movementSpeed;
			break;
		case Still:
			velocity.x = 0;
			velocity.y = 0;
			break;
		}

		position.x += velocity.x;
		position.y += velocity.y;

	}

	Turn GetTurn() {
		float maxDif = 20.0f;
		// Manually set up left and right motor ports.
		MotorPort leftMotorPort = port1;
		MotorPort rightMotorPort = port2;
		int leftMotor = motor[leftMotorPort];
		int rightMotor = motor[rightMotorPort];

		if (rightMotor > leftMotor && abs(rightMotor - leftMotor) > maxDif) {
			return LeftTurn;
		}
		if (rightMotor < leftMotor && abs(rightMotor - leftMotor) > maxDif) {
			return RightTurn;
		}
		if (abs(rightMotor) > maxDif && abs(leftMotor) > maxDif) {
			return MOVIN;
		}

		return Still;
	}



};