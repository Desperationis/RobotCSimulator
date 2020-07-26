#pragma once
#include <SFML\Graphics.hpp>
#include "../Utility/TextureSprite.h"
#include "../Utility/DeltaClock.h"
#include "../stdafx.h"
#include "../RobotC.h"

using namespace RobotC::Peripherals;
using namespace RobotC::Types;

class Robot : public TextureSprite {
public:
	float GetRadians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}

	Robot() : SPEED(500), STATICFRICTION(20), velocity(0, 0), canOvercomeFriction(false) {

		LoadTextureFromFile("Assets/Clawbot.png");
		SetRectSize(sf::Vector2f(50, 50));

		setOrigin(sf::Vector2f(25, 25));
		setPosition(sf::Vector2f(500, 500));

		turnSpeed = (SPEED / ((float)rectangleShape.getLocalBounds().width * M_PI)) * 360;

	};

	void Update() override {
		auto delta = DeltaClock::GetDelta();
		canOvercomeFriction = abs(motor[leftMotorPort]) + abs(motor[rightMotorPort]) > STATICFRICTION;

		if (canOvercomeFriction) {
			UpdateTurning(delta);
			UpdateVelocity(delta);
		}
	};

	void UpdateTurning(float delta) {
		// Turn based on motor's values.
		float angularSpeed = ((motor[leftMotorPort] - motor[rightMotorPort]) / 254.0f) * turnSpeed;
		rotate(angularSpeed * delta);
	}

	void UpdateVelocity(float delta) {
		// Set velocity based on motor values
		float radianAngle = GetRadians(getRotation());
		float combinedSpeed = ((motor[leftMotorPort] + motor[rightMotorPort]) / 254.0f) * SPEED;
		
		velocity.x = cos(radianAngle) * combinedSpeed * delta;
		velocity.y = sin(radianAngle) * combinedSpeed * delta;

		move(velocity);
	}


private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	const float SPEED;
	const float STATICFRICTION;


	float turnSpeed;
	sf::Vector2f velocity;
	bool canOvercomeFriction;
};