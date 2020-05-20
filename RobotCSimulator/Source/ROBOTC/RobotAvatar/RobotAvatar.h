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

class RobotAvatar : public sf::Drawable {
private:
	// Drawing variables
	sf::RectangleShape rect;
	sf::Texture texture;

	// Movement
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
	float turnSpeed;
	float angle;

	// Motors and Sensors
	short& leftMotorValue;
	short& rightMotorValue;
	short& leftEncoderValue;
	short& rightEncoderValue;

public:
	enum Turn {LeftTurn, RightTurn, Still, MOVIN};

	RobotAvatar();

	float GetRadians(float degree);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void Update();

	void UpdateVelocity();

	void UpdateTurning();

	Turn GetTurn();
};