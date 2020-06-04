#pragma once
#include <SFML/Graphics.hpp>

/*
 *	ROBOT_AVATAR_SETTINGS.H
 *
 * A namespace used to change particular settings of the robot avatar.
*/

namespace ROBOT_AVATAR_SETTINGS {

	// Looks
	static const char* textureFileName = "Assets\\Clawbot.png"; // File name of texture to be loaded up.
	static sf::Vector2f size(80, 80);							// Size of robot avatar texture.
	static sf::Vector2f initialPosition(800, 800);				// Initial position of robot avatar.
	static float initialAngle = 0;								// Initial angle of robot avatar.

	// Physics
	static float speed = 600;									// Pixels traveled in a given second.
	static float encoderTurnTime = 1.0f;						// Number of seconds required for 1 wheel turn.
	static int staticFriction = 40;								// Motor value required to overcome static friction.
}