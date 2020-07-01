/*****************************************************************//**
 * \file   RobotAvatar.h
 * \brief  A little robot on screen that reacts to the motor value!
 *********************************************************************/

#include <SFML/Graphics.hpp>
#include <memory>
#include <Time/DeltaClock.h>
#include <ClassicSprite.h>
#include "../ROBOTCtoC++/RobotC.h"
#include "ROBOT_AVATAR_SETTINGS.h"

#define M_PI 3.1415


/**
 * A sprite on screen that simulates robot hardware. 
 * Moves accordingly to motor values.
 */
class RobotAvatar : public ClassicSprite {
private:

	// Movement

	/**
	 * Velocity of the robot, represented by a vector.
	 */
	sf::Vector2f velocity;

	/**
	 * The angular turn speed of the robot, calculated using
	 * the width of the texture and the current speed setting.
	 */
	float calculatedTurnSpeed;
	bool canOvercomeFriction;

	// Motors and Sensors
	short& leftMotorValue;
	short& rightMotorValue;
	float& leftEncoderValue;
	float& rightEncoderValue;

public:
	/**
	 * This class should be created once the program has started running, as 
	 * it reads motor and encoder values from the global motor array.
	 */
	RobotAvatar();

	/**
	 * Updates the robot.
	 */
	void Update();

private:
	float GetRadians(float degree);

	void UpdateVelocity(float delta);

	void UpdateTurning(float delta);

	void UpdateFriction();

	void UpdateEncoders(float delta);

	void UpdateLoop();

};