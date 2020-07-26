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
		setPosition(sf::Vector2f(getPosition().x + 1, getPosition().y));
	};


private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	const float SPEED;
	const float STATICFRICTION;

	float turnSpeed;
	sf::Vector2f velocity;
	bool canOvercomeFriction;
};