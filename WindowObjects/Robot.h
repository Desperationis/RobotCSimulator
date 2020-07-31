#pragma once
#include <SFML\Graphics.hpp>
#include "../Utility/TextureSprite.h"
#include "../Utility/DeltaClock.h"
#include "../stdafx.h"
#include "../RobotC.h"

using namespace RobotC::Peripherals;
using namespace RobotC::Types;
using namespace RobotC::Functions;

class RobotTable;
class RobotVisuals;
class Robot : public TextureSprite {
public:
	Robot() : speed(50), pixelsNeededToTurn(50), renderICC(false) {
		LoadTextureFromFile("Assets/Clawbot.png");
		SetRectSize(sf::Vector2f(50, 100));

		// Origin defines the midpoint of the wheels. 
		setOrigin(sf::Vector2f(rectangleShape.getLocalBounds().width / 2, rectangleShape.getLocalBounds().height / 2));
		setPosition(sf::Vector2f(1000, 500));
	};

	sf::Vector2f GetWrappedPosition(sf::Vector2f position) {
		// Wrap the robot's position so it's always in view.
		sf::VideoMode windowMode = sf::VideoMode::getDesktopMode();

		if(position.x > windowMode.width) {
			position.x = 0;
		}
		if (position.x < 0) {
			position.x = windowMode.width;
		}
		
		if (position.y > windowMode.height) {
			position.y = 0;
		}
		if (position.y < 0) {
			position.y = windowMode.height;
		}

		return position;
	}

	sf::Vector2f CalculateNewTurnPosition(float leftMotorValue, float rightMotorValue) {
		const auto delta = DeltaClock::GetDelta();
		auto position = getPosition();

		// Use a modified formula of tangetial velocity to find circle center (ICC) + rotational speed.
		const float width = rectangleShape.getLocalBounds().width;
		const float distanceToICC = (width / 2) * ((leftMotorValue + rightMotorValue) / (rightMotorValue - leftMotorValue));
		const float rotationalSpeed = (rightMotorValue - leftMotorValue) / width;
		const float maxRotationalSpeed = 254.0f / width;
		
		// Make a turn around a pivot (ICC) based on rotational speed.
		ICCPosition.x = getPosition().x + (sinDegrees(getRotation()) * distanceToICC);
		ICCPosition.y = getPosition().y - (cosDegrees(getRotation()) * distanceToICC);

		float ICCCircumference = distanceToICC * 2 * PI;
		float distanceCovered = maxRotationalSpeed * ICCCircumference;

		// Scale down the rotation speed in such a way where the maximum arc distance covered in a second is equivalent to speed (px).
		setRotation(getRotation() - ((rotationalSpeed / maxRotationalSpeed) * (speed / (width * PI)) * delta * 360));

		position.x = ICCPosition.x + (-sinDegrees(getRotation()) * distanceToICC);
		position.y = ICCPosition.y + (cosDegrees(getRotation()) * distanceToICC);
		
		return position;
	}

	void Update() override {

		// Scale raw motor values down to emulate speed
		const float leftMotorValue = motor[leftMotorPort];
		const float rightMotorValue = motor[rightMotorPort];

		UpdateSensors();

		sf::Vector2f position = getPosition();

		// Turn or go straight based on motor velocities.
		if(abs(rightMotorValue - leftMotorValue) >= 2) {
			position = CalculateNewTurnPosition(leftMotorValue, rightMotorValue);
		}
		else {
			auto delta = DeltaClock::GetDelta();
			position.x += ((leftMotorValue / 127.0f) * speed * cosDegrees(getRotation()) * delta);
			position.y += ((leftMotorValue / 127.0f) * speed * sinDegrees(getRotation()) * delta);
		}

		velocity.x = position.x - getPosition().x;
		velocity.y = position.y - getPosition().y;

		setPosition(GetWrappedPosition(position));
	};

	void UpdateSensors() {
		auto delta = DeltaClock::GetDelta();

		// Sensors care about the actual, real-world value.
		const float leftMotorValue = RobotC::Peripherals::GetConvertedMotorValue(leftMotorPort);
		const float rightMotorValue = RobotC::Peripherals::GetConvertedMotorValue(rightMotorPort);

		// In the real world, encoders use strips of black lines to tell their position.
		// Each time the infrared beam of the encoder hits a black line, it increments its
		// counter by a single tick; no decimal. This "snapping" mechanism can be replicated
		// by using floats as buffers for converting into short ints.
		float leftDistanceInDelta = (leftMotorValue / 127.0f) * speed * delta;
		float rightDistanceInDelta = (rightMotorValue / 127.0f) * speed * delta;

		encoderBuffer.x += (leftDistanceInDelta / pixelsNeededToTurn) * 360;
		encoderBuffer.y += (rightDistanceInDelta / pixelsNeededToTurn) * 360;

		SensorValue[leftEncoderPort] = encoderBuffer.x;
		SensorValue[rightEncoderPort] = encoderBuffer.y;
	}

private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	SensorPort leftEncoderPort = dgtl1;
	SensorPort rightEncoderPort = dgtl3;

	sf::Vector2f encoderBuffer;

	sf::Vector2f ICCPosition;
	sf::Vector2f velocity;

	int speed;
	int pixelsNeededToTurn;
	bool renderICC;

	friend class RobotTable;
	friend class RobotVisuals;
};