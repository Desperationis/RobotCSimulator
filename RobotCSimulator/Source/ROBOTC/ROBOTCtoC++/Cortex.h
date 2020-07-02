#pragma once
#include "RobotC.h"
#include <thread>
#include <functional>
#include <array>
#include <vector>
#include <string>
#include <memory>

/**
 * The cortex of the robot! Holds information about sensors, motors, and running threads.
 */
class Cortex {
public:
	Cortex() = default;

	static void config(std::string name, MotorPort& motorPort, MotorPort port, bool reversed = false);
	static void config(std::string name, SensorPort& motorPort, SensorPort port);

	// My own classes
	static std::vector<std::unique_ptr<std::thread>> threads;
	static std::array<std::unique_ptr<SensorInfo>, 20> sensorInfo;
	static std::array<std::unique_ptr<MotorInfo>, 10> motorInfo;
};

// Pure RobotC Variables
extern std::array<short, 10> motor;
extern std::array<float, 20> SensorValue;
extern std::array<short, 16> vexRT;