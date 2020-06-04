#include "../ROBOTCtoC++/RobotC.h"
#include "Slew.h"
#include "Helpers.h"
#include "Globals.h"
#include <iostream>

#ifndef SLEW_SOURCE
#define SLEW_SOURCE

// TODO:
// 		PID Control


// Positive Power turns left motor clockwise. + Forward - Backward

// Left Axle Variables
// Ch4: X <- Ch3: Y Positive Down

// Right Axle Variables
// Ch1: X -> Ch2: Y Positive Down

short slewMotor[10];
bool slewWhitelist[10];
ubyte slewStep;

void InitSlew() {
	for(short i = 0; i < 10; i++) {
		slewMotor[i] = 0;
		slewWhitelist[i] = false;
	}
}

task Slew() {
	while(true) {
		for(short i = 0; i < 10; i++) {
			if(CanSlew(i)) {
				motor[i] = Clamp(SlewStep(motor[i], GetSlewStep(), slewMotor[i] * GetControllerSpeed()));
			}
		}
		delay(GetDelay());
	}
}

void SetMotorSlew(tMotor port, byte speed) {

	// Only slew motor if it is enabled.
	if(CanSlew(port)){
		slewMotor[port] = speed;
	}
	else {
		motor[port] = speed;
	}
}

void AllowSlew(tMotor port) {
	slewWhitelist[port] = true;
}

bool CanSlew(tMotor port) {
	return slewWhitelist[port];
}

void SetSlewStep(ubyte step) {
	slewStep = step;
}

ubyte GetSlewStep() {
	return slewStep;
}

#endif
