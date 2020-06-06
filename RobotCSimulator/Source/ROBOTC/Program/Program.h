#include "../ROBOTCtoC++/RobotC.h"
#include "Controllers.h"
#include "Globals.h"
#include "Helpers.h"
#include "Slew.h"
#include "PID.h"
#include "Setup.h"
#include <iostream>

SensorPort leftEncoder;
SensorPort rightEncoder;
MotorPort leftMotor;
MotorPort rightMotor;
void SetUp() {
	config("leftEncoder", leftEncoder, dgtl1);
	config("rightEncoder", rightEncoder, dgtl3);
	config("leftMotor", leftMotor, port1, false);
	config("rightMotor", rightMotor, port5, true);
}

task programMain() {
	InitCustomLibrary();

	SetLeftMotor(leftMotor);
	SetRightMotor(rightMotor);
	AllowSlew(leftMotor, true);
	AllowSlew(rightMotor, true);

	SetLeftEncoder(leftEncoder);
	SetRightEncoder(rightEncoder);
	SetAverageDelay(20);
	SetMaxSpeed(0.8);
	SetSlewStep(30);

	startTask(Slew);
	startTask(PID);

	AllowPID(true);
	SetK(1.1, 0.0, 0.0);
	SetPIDTarget(LEFT, 300);
	SetPIDTarget(RIGHT, 400);

	//startTask(GamerControl);
	while(true) {
		// Keep program alive.
		delay(GetDelay());
	}
}
