#include "RobotAvatar.h"
#include "../Program/Globals.h"
#include <iostream>

template <typename T>
T amax(T a, T b) {
	if (abs(a) > abs(b)) {
		return a;
	}
	return b;
}

float RobotAvatar::GetRadians(float degrees) {
	return angle * (M_PI / 180.0f);
}

RobotAvatar::RobotAvatar() : leftMotorValue(motor.at(GetLeftMotor())), 
							 rightMotorValue(motor.at(GetRightMotor())),
							 leftEncoderValue(SensorValue.at(GetLeftEncoder())), 
							 rightEncoderValue(SensorValue.at(GetRightEncoder())) {

	// Load texture.
	texture.loadFromFile("Assets\\Clawbot.png");
	rect.setTexture(&texture);
	rect.setSize(sf::Vector2f(80, 80));

	// Position variables.
	position.x = 300;
	position.y = 500;
	angle = 0.0f;

	// Speed variables
	velocity.x = velocity.y = 0;
	turnSpeed = 5;
	speed = 5;
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
	if (abs(leftMotorValue) + abs(rightMotorValue) > staticFriction) {
		float angularSpeed = ((leftMotorValue - rightMotorValue) / 254.0f) * turnSpeed;
		angle += angularSpeed;
	}
}

void RobotAvatar::UpdateVelocity() {
	// Set velocity based on motor values
	if (abs(leftMotorValue) > staticFriction || abs(rightMotorValue) > staticFriction) {
		float relativeSpeed = ((leftMotorValue + rightMotorValue) / 254.0f) * speed;

		velocity.x = cos(GetRadians(angle)) * relativeSpeed;
		velocity.y = sin(GetRadians(angle)) * relativeSpeed;

		leftEncoderValue += leftMotorValue / 20.0f;
		rightEncoderValue += rightMotorValue / 20.0f;

		position.x += velocity.x;
		position.y += velocity.y;
	}
}