#include "Helpers.h"
#include "Slew.h"
#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#include "Externs.h"
#ifndef CONTROLLERS_SOURCE
#define CONTROLLERS_SOURCE


/*
	Diego's Controller Tips:

	Positive Power turns left motor clockwise. + Forward - Backward

	Left Axle Variables
	Ch4: X <- Ch3: Y Positive Down

	Right Axle Variables
	Ch1: X -> Ch2: Y Positive Down

*/


/**
 * Arcade control on the left joystick.
 * Tries to slew if possible.
*/
task LeftArcadeControl() {
	while ((true) && !killAll) {
		SetSlewMotor(LEFT_MOTOR_PORT,  MotorClamp(-vexRT[Ch3] - vexRT[Ch4]));
		SetSlewMotor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch3] + vexRT[Ch4]));
		delay(TASK_DELAY);
	}
}


/**
 * Arcade control on the right joystick.
 * Tries to slew if possible.
*/
task RightArcadeControl() {
	while ((true) && !killAll) {
		SetSlewMotor(LEFT_MOTOR_PORT,  MotorClamp(vexRT[Ch2] + vexRT[Ch1]));
		SetSlewMotor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch2] - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}


/**
 * Tank control!
 * Tries to slew if possible.
*/
task CustomTankControl() {
	while ((true) && !killAll) {
		SetSlewMotor(LEFT_MOTOR_PORT,  MotorClamp(-vexRT[Ch3]));
		SetSlewMotor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch2]));

		delay(TASK_DELAY);
	}
}


/**
 * Racecar-like controls.
 * Tries to slew if possible.
*/
task GamerControl() {
	while ((true) && !killAll) {
		// Left Axis: up / down
		// Right Axis: right / left
		SetSlewMotor(LEFT_MOTOR_PORT,  MotorClamp(-vexRT[Ch3] + vexRT[Ch1]));
		SetSlewMotor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch3] - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}


#endif
