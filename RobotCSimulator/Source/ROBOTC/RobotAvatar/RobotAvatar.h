#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <Time/DeltaClock.h>
#include "../ROBOTCtoC++/RobotC.h"
#include "ROBOT_AVATAR_SETTINGS.h"

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
	float angle;
	float calculatedTurnSpeed;
	bool canOvercomeFriction;

	// Motors and Sensors
	short& leftMotorValue;
	short& rightMotorValue;
	float& leftEncoderValue;
	float& rightEncoderValue;

public:
	RobotAvatar();

	float GetRadians(float degree);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void Update();

	void UpdateVelocity(float delta);

	void UpdateTurning(float delta);

	void UpdateFriction();

	void UpdateEncoders(float delta);
};