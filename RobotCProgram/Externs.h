#pragma once
#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;


extern short target[2];
extern bool canPID;
extern short slewMotor[10];
extern bool slewWhitelist[10];
extern ubyte slewStep;
extern ubyte slewStep;
extern tMotor leftMotorPort;
extern tSensors leftEncoderPort;
extern tMotor rightMotorPort;
extern tSensors rightEncoderPort;
extern ubyte taskDelay;
extern ubyte taskDelay;
extern float maxSpeed;
