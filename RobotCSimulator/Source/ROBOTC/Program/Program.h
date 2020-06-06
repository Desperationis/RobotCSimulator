#include "../ROBOTCtoC++/RobotC.h"
#include "Controllers.h"
#include "Globals.h"
#include "Helpers.h"
#include "Slew.h"
#include "PID.h"
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
	ResetEncoders();
	InitSlew();
	startTask(Slew);

	SetLeftMotor(leftMotor);
	SetRightMotor(rightMotor);
	AllowSlew(leftMotor);
	AllowSlew(rightMotor);

	SetLeftEncoder(leftEncoder);
	SetRightEncoder(rightEncoder);
	SetAverageDelay(20);
	SetControllerSpeed(0.9);
	SetSlewStep(10);

	PID(500);
	//startTask(GamerControl);
	while(true) {
		// Keep program alive.
		delay(GetDelay());
	}
}
