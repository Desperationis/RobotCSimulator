#pragma once
#include "RobotC.h"

// Variables needs to be defined only once
std::array<int, 10> motor;
std::array<std::unique_ptr<MotorInfo>, 10> motorInfo;
std::array<int, 16> vexRT;