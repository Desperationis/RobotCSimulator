#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#include "Externs.h"
#ifndef SETUP_SOURCE
#define SETUP_SOURCE

#define TASK_DELAY 20

// Used for controllers
#define LEFT_MOTOR_PORT leftMotor
#define RIGHT_MOTOR_PORT rightMotor

#define SLEW_STEP 15

#endif
