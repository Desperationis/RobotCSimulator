#include "RobotAvatar.h"
#include "../Program/Globals.h"
#include <iostream>

float RobotAvatar::GetRadians(float degrees) {
	return angle * (M_PI / 180.0f);
}

RobotAvatar::RobotAvatar() : leftMotorValue(motor.at(GetLeftMotor())), 
							 rightMotorValue(motor.at(GetRightMotor())),
							 leftEncoderValue(SensorValue.at(GetLeftEncoder())), 
							 rightEncoderValue(SensorValue.at(GetRightEncoder())) {

	// Load texture.
	texture.loadFromFile("Assets\\Clawbot.jpg");
	rect.setTexture(&texture);
	rect.setSize(sf::Vector2f(80, 80));

	// Position variables.
	position.x = 300;
	position.y = 500;
	angle = 0.0f;

	// Speed variables
	velocity.x = velocity.y = 0;
	turnSpeed = 5;
	speed = 10;
	staticFriction = 30; // Motor Value it takes to overcome static friction

	// Origin in center.
	sf::Vector2f newOrigin;
	newOrigin.x = rect.getLocalBounds().width / 2;
	newOrigin.y = rect.getLocalBounds().height / 2;
	rect.setOrigin(newOrigin);
}

void RobotAvatar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(position);
	states.transform.rotate(angle);

	target.draw(rect, states);
}

void RobotAvatar::Update() {
	UpdateTurning();
	UpdateVelocity();
}

void RobotAvatar::UpdateTurning() {
	// Turn based on motor's values.
	if (abs(leftMotorValue) > staticFriction || abs(rightMotorValue) > staticFriction) {
		float angularSpeed = turnSpeed * (abs(leftMotorValue - rightMotorValue) / 254.0f);
		if (leftMotorValue > rightMotorValue) {
			angle += angularSpeed;
		}
		else if (leftMotorValue < rightMotorValue) {
			angle -= angularSpeed;
		}
	}
}

void RobotAvatar::UpdateVelocity() {
	// Set velocity based on motor values
	if (abs(leftMotorValue) > staticFriction || abs(rightMotorValue) > staticFriction) {
		switch (GetTurn()) {
		case LeftTurn:
			velocity.x = cos(GetRadians(angle)) * (rightMotorValue / 254.0f) * speed;
			velocity.y = sin(GetRadians(angle)) * (rightMotorValue / 254.0f) * speed;

			leftEncoderValue -= abs(leftMotorValue) / 20;
			rightEncoderValue -= abs(rightMotorValue) / 20;

			break;
		case RightTurn:
			velocity.x = cos(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;
			velocity.y = sin(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;

			leftEncoderValue += abs(leftMotorValue) / 20;
			rightEncoderValue += abs(rightMotorValue) / 20;
			break;
		case MOVIN:
			velocity.x = cos(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;
			velocity.y = sin(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;

			leftEncoderValue += leftMotorValue / 20;
			rightEncoderValue -= rightMotorValue / 20;
			break;
		case Still:
			velocity.x = 0;
			velocity.y = 0;
			break;
		}

		position.x += velocity.x;
		position.y += velocity.y;
	}
}

RobotAvatar::Turn RobotAvatar::GetTurn() {
	float maxDif = 20.0f;

	if (rightMotorValue > leftMotorValue && abs(rightMotorValue - leftMotorValue) > maxDif) {
		return LeftTurn;
	}
	if (rightMotorValue < leftMotorValue && abs(rightMotorValue - leftMotorValue) > maxDif) {
		return RightTurn;
	}
	if (abs(rightMotorValue) > maxDif && abs(leftMotorValue) > maxDif) {
		return MOVIN;
	}

	return Still;
}