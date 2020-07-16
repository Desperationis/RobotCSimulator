#include "Helpers.h"
#include "Slew.h"
#include "PID.h"
#include "Setup.h"
#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#ifndef SETUP_SOURCE
#define SETUP_SOURCE



void InitCustomLibrary() {
	ResetEncoders();
	InitPID();
	InitSlew();
}


#endif
