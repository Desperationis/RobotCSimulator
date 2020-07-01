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

// start
// Notes:
// You can download files from cortex using Robot > Advanced Tools > File Management
// You can download view joystick values using Robot > Advanced Tools > Joystick Viewer
// You can check battery level by using nImmediateBatterLevel; Found in Battery > Variables
// You can use controller accelerameter values.

// Running tasks PID() and Slew() will give you 8 concurrent tassks left.

void GoForward(int amount);

task programMain() {
	InitCustomLibrary();

	// Global Settings
	SetAverageDelay(20);
	SetMaxSpeed(1);

	// Tell the library our chassis sensors and motors.
	SetLeftMotor(leftMotor);
	SetRightMotor(rightMotor);
	SetLeftEncoder(leftEncoder);
	SetRightEncoder(rightEncoder);

	delay(2000); // Delay for RobotCSimulator.

	// Activate Controllers
	startTask(Slew);
	startTask(PID);

	// Slew Settings
	AllowSlew(leftMotor, true);
	AllowSlew(rightMotor, true);
	SetSlewStep(30);

	// PID Settings
	startTask(GamerControl);

	while(true) {
		// Keep program alive.
		delay(GetDelay());
	}
}

void GoForward(int amount) {
	SetPIDTarget(LEFT, amount);
	SetPIDTarget(RIGHT, amount);

	while(!BothHasReached(leftEncoder, rightEncoder, -amount, 10)) {
		// Keep program alive.
		delay(GetDelay());
	}
}
