#pragma once
#include "../ROBOTCtoC++/RobotC.h"
#include "CLibrary.h"

/*
 * Program.h
 *
 * Used for function definitions for Program.cpp.
 */


MotorPort leftMotor, rightMotor;

void SetUp() {
	config("leftMotor", leftMotor, port1, false);
	config("rightMotor", rightMotor, port2, true);
}

task programMain()
{
	SetAverageDelay(20);
	SetLeftMotor(port1);
	SetRightMotor(port2);
	SetControllerSpeed(1);
	startTask(GamerControl);

	while (true) {
		// Keep program alive.
		delay(20);
	}
}