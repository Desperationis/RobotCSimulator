#include "PID.h"
#include "Slew.h"
#include "Helpers.h"
#include "../ROBOTCtoC++/RobotC.h"
#include "../ROBOTCtoC++/Cortex.h"
#include <iostream>
#include <cmath>

#ifndef SETUP_SOURCE
#define SETUP_SOURCE



void InitCustomLibrary() {
	ResetEncoders();
	InitPID();
	InitSlew();
}


#endif
