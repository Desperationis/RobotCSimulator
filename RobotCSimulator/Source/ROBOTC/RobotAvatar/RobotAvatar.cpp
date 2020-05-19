#include "RobotAvatar.h"

int RobotAvatar::GetRadians(float degrees) {
	return angle * (M_PI / 180.0f);
}

RobotAvatar::RobotAvatar() {
	// Load texture.
	texture.loadFromFile("Assets\\Clawbot.jpg");
	rect.setTexture(&texture);
	rect.setSize(sf::Vector2f(80, 80));

	// Initial position and speed.
	position.x = 900;
	position.y = 700;
	velocity.x = 0;
	velocity.y = 0;

	turnSpeed = 5;
	speed = 10;

	// Origin in center.
	sf::Vector2f newOrigin;
	newOrigin.x = rect.getLocalBounds().width / 2;
	newOrigin.y = rect.getLocalBounds().height / 2;
	rect.setOrigin(newOrigin);

	leftMotorValue = rightMotorValue = 0;
	leftEncoderValue = rightEncoderValue = 0;
}

void RobotAvatar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(position);
	states.transform.rotate(angle);

	target.draw(rect, states);
}

void RobotAvatar::Update() {
	UpdateTurning();
	UpdateVelocity();
	UpdateMotors();
	UpdateSensors();
}

void RobotAvatar::UpdateMotors() {
	leftMotorValue = motor[port1];
	rightMotorValue = motor[port2];
}

void RobotAvatar::UpdateSensors() {
	SensorValue[dgtl1] = leftEncoderValue;
	SensorValue[dgtl3] = rightEncoderValue;
}

void RobotAvatar::UpdateTurning() {
	// Turn based on motor's values.

	float speed = turnSpeed * (abs(leftMotorValue - rightMotorValue) / 254.0f);
	if (leftMotorValue > rightMotorValue) {
		angle += speed;
	}
	else if (leftMotorValue < rightMotorValue) {
		angle -= speed;
	}
}

void RobotAvatar::UpdateVelocity() {
	// Set velocity
	switch (GetTurn()) {
	case LeftTurn:
		velocity.x = cos(GetRadians(angle)) * (rightMotorValue / 254.0f) * speed;
		velocity.y = sin(GetRadians(angle)) * (rightMotorValue / 254.0f) * speed;

		leftEncoderValue -= leftMotorValue / 4;
		rightEncoderValue += rightMotorValue / 4;

		break;
	case RightTurn:
		velocity.x = cos(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;
		velocity.y = sin(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;

		leftEncoderValue += leftMotorValue / 4;
		rightEncoderValue -= rightMotorValue / 4;
		break;
	case MOVIN:
		velocity.x = cos(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;
		velocity.y = sin(GetRadians(angle)) * (leftMotorValue / 254.0f) * speed;

		leftEncoderValue += leftMotorValue / 4;
		rightEncoderValue += rightMotorValue / 4;
		break;
	case Still:
		velocity.x = 0;
		velocity.y = 0;
		break;
	}

	position.x += velocity.x;
	position.y += velocity.y;
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