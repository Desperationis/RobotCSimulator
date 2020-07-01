#include "RobotAvatar.h"
#include "../Program/Globals.h"
#include <iostream>


RobotAvatar::RobotAvatar() : leftMotorValue(motor.at(GetLeftMotor())), 
							 rightMotorValue(motor.at(GetRightMotor())),
							 leftEncoderValue(SensorValue.at(GetLeftEncoder())), 
							 rightEncoderValue(SensorValue.at(GetRightEncoder())) {

	auto& textureFileName = ROBOT_AVATAR_SETTINGS::textureFileName;
	auto& size = ROBOT_AVATAR_SETTINGS::size;

	// Load texture.
	LoadTextureFromFile(textureFileName);
	SetSize(size);

	auto& initialPosition = ROBOT_AVATAR_SETTINGS::initialPosition;
	auto& initialAngle = ROBOT_AVATAR_SETTINGS::initialAngle;

	// Position variables.
	setPosition(initialPosition);
	setRotation(initialAngle);

	auto& speed = ROBOT_AVATAR_SETTINGS::speed;

	// Speed variables
	velocity = sf::Vector2f(0, 0);
	calculatedTurnSpeed = (speed / ((float)rect.getLocalBounds().width * M_PI)) * 360;

	// Origin in center.
	sf::Vector2f newOrigin;
	newOrigin.x = rect.getLocalBounds().width / 2;
	newOrigin.y = rect.getLocalBounds().height / 2;
	setOrigin(newOrigin);
}

void RobotAvatar::Update() {
	auto delta = DeltaClock::GetDelta();
	UpdateFriction();

	// Only move if static friction is overcome.
	if (canOvercomeFriction) {
		UpdateTurning(delta);
		UpdateVelocity(delta);
		UpdateEncoders(delta);
	}

	UpdateLoop();
}

void RobotAvatar::UpdateFriction() {
	auto& staticFriction = ROBOT_AVATAR_SETTINGS::staticFriction;

	canOvercomeFriction = abs(leftMotorValue) + abs(rightMotorValue) > staticFriction;
}

void RobotAvatar::UpdateTurning(float delta) {
	// Turn based on motor's values.
	float angularSpeed = ((leftMotorValue - rightMotorValue) / 254.0f) * calculatedTurnSpeed;
	rotate(angularSpeed * delta);
}

void RobotAvatar::UpdateVelocity(float delta) {
	auto& speed = ROBOT_AVATAR_SETTINGS::speed;

	// Set velocity based on motor values
	float radianAngle = GetRadians(getRotation());
	float combinedSpeed = ((leftMotorValue + rightMotorValue) / 254.0f) * speed;

	velocity.x = cos(radianAngle) * combinedSpeed * delta;
	velocity.y = sin(radianAngle) * combinedSpeed * delta;

	move(velocity);
}

void RobotAvatar::UpdateEncoders(float delta) {
	auto& turnTime = ROBOT_AVATAR_SETTINGS::encoderTurnTime;

	// Set velocity based on motor values
	float leftEncoderSpeed = ((float)leftMotorValue / 127.0f) * 360.0f;
	float rightEncoderSpeed = ((float)rightMotorValue / 127.0f) * 360.0f;

	leftEncoderValue += leftEncoderSpeed * delta * turnTime;
	rightEncoderValue -= rightEncoderSpeed * delta * turnTime;

	move(velocity);
}

void RobotAvatar::UpdateLoop() {
	// Basic Screen Wrap

	float width = rect.getLocalBounds().width;
	float height = rect.getLocalBounds().height;

	float maxX = 1500 + width;
	float maxY = 900 + height;

	float minX = 0 - width;
	float minY = 0 - height;

	auto position = getPosition();

	if (position.x > maxX) {
		position.x = minX;
	}
	else if (position.x < minX) {
		position.x = maxX;
	}

	if (position.y > maxY) {
		position.y = minY;
	}
	else if (position.y < minY) {
		position.y = maxY;
	}

	setPosition(position);
}