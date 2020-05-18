#pragma once
#include "RobotC.h"

// Variables needs to be defined only once
std::array<int, 16> vexRT;
std::array<int, 10> motor;
std::array<std::unique_ptr<MotorInfo>, 10> motorInfo;
std::array<int, 20> SensorValue;
std::array<std::unique_ptr<SensorInfo>, 20> sensorInfo;
std::vector<std::unique_ptr<std::thread>> threads;