#include "../ROBOTCtoC++/RobotC.h"
#include "PID.h"
#include "Helpers.h"
#include "Globals.h"
#include "Slew.h"
#include <iostream>

#ifndef PID_SOURCE
#define PID_SOURCE


PIDInfo leftPID;
PIDInfo rightPID;



short PIDCalculate(short encoderValue, short target, PIDInfo* info ) {
	// Calculate motor speed with PID info.
	info->proportion = target - encoderValue;

	info->integral += info->proportion;
	info->derivative = info->proportion - info->pastError;

	info->pastError = info->proportion;

	if(abs(info->proportion) < 5) {
		info->integral = 0;
	}

	return Clamp((info->proportion * info->kP) + (info->integral * info->kI) + (info->derivative * info->kD));
}

void PID(short target) {
	double kP = 1.1;
	double kI = 0.0;
	double kD = 0;

	leftPID.kP = kP;
	leftPID.kI = kI;
	leftPID.kD = kD;

	rightPID.kP = kP;
	rightPID.kI = kI;
	rightPID.kD = kD;

	while(true) {
		SetMotorSlew( GetLeftMotor(), PIDCalculate(SensorValue[GetLeftEncoder()], target, &leftPID));
		SetMotorSlew( GetRightMotor(), PIDCalculate(-SensorValue[GetRightEncoder()], target, &rightPID));

		delay(GetDelay());
	}
}

#endif
