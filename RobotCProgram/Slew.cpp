#include "Slew.h"
#include "Globals.h"
#include "Helpers.h"
#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#ifndef SLEW_SOURCE
#define SLEW_SOURCE


short slewMotor[10];
bool slewWhitelist[10];
ubyte slewStep;


void InitSlew() {
	for(short i = 0; i < 10; i++) {
		slewMotor[i] = 0;
		slewWhitelist[i] = false;
	}
	slewStep = 0;
}


task Slew() {
	while(true && !killAll) {
		for(short i = 0; i < 10; i++) {
			if(CanSlew(i)) {
				motor[i] = Clamp(SlewStep(motor[i], GetSlewStep(), slewMotor[i] * GetMaxSpeed()));
			}
		}
		delay(GetDelay());
	}
}


void SetSlewStep(ubyte step) {
	slewStep = step;
}


ubyte GetSlewStep() {
	return slewStep;
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


void AllowSlew(tMotor port, bool active) {
	slewWhitelist[port] = active;
}


bool CanSlew(tMotor port) {
	return slewWhitelist[port];
}


#endif
