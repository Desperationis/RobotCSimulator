#include "RobotC.h"

using namespace RobotC::Functions;

const float RobotC::Functions::PI = 3.1415;

/**
 * Returns -1, 0, or 1 depending on the sign of the integer.
 * 
 * \param input The integer.
 * \return -1, 0, or 1 depending on the sign of the integer.
 */
int RobotC::Functions::sgn(int input) {
	return input > 0 ? 1 : (input < 0 ? -1 : 0);
}

float RobotC::Functions::degreesToRadians(float degrees) {
	return degrees * (PI / 180.0f);
}

float RobotC::Functions::radiansToDegrees(float radians) {
	return radians * (180.0f / PI);
}

float RobotC::Functions::cosDegrees(float degrees) {
	return cos(degreesToRadians(degrees));
}

float RobotC::Functions::sinDegrees(float degrees) {
	return sin(degreesToRadians(degrees));
}
