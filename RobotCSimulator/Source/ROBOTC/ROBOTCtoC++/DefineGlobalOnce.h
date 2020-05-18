#pragma once
#include "RobotC.h"

/*
 * DefineGlobalOnce.h
 *
 * Defines global core RobotC variables once.
 */

// Pure RobotC
std::array<int, 16> vexRT;
std::array<int, 10> motor;
std::array<int, 20> SensorValue;

// My variables
std::array<std::unique_ptr<MotorInfo>, 10> motorInfo;
std::array<std::unique_ptr<SensorInfo>, 20> sensorInfo;
std::vector<std::unique_ptr<std::thread>> threads;