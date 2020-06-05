#include "RobotC.h"

void startTask(std::function<task()> func) {
	threads.push_back(std::make_unique<std::thread>(func));
}

void delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void config(std::string name, MotorPort& motorPort, MotorPort port, bool reverse) {
	motorPort = port;
	motorInfo[port] = std::make_unique<MotorInfo>(name, reverse);
}

void config(std::string name, SensorPort& sensorPort, SensorPort port) {
	sensorPort = port;
	sensorInfo[port] = std::make_unique<SensorInfo>(name);
}

int sgn(int input) {
	if (input < 0) {
		return -1;
	}
	if (input > 0) {
		return 1;
	}

	return 0;
}