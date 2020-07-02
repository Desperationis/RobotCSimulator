#include "Cortex.h"

std::vector<std::unique_ptr<std::thread>> Cortex::threads;
std::array<std::unique_ptr<SensorInfo>, 20> Cortex::sensorInfo;
std::array<std::unique_ptr<MotorInfo>, 10> Cortex::motorInfo;

Cortex::Cortex() {
	// Initialize information structs.
	for (int i = 0; i < Cortex::motorInfo.max_size(); i++) {
		Cortex::motorInfo[i] = std::make_unique<MotorInfo>("<none>", false);
	}
	for (int i = 0; i < Cortex::sensorInfo.max_size(); i++) {
		Cortex::sensorInfo[i] = std::make_unique<SensorInfo>("<none>");
	}
}

void Cortex::config(std::string name, MotorPort& motorPort, MotorPort port, bool reverse) {
	motorPort = port;
	motorInfo[port] = std::make_unique<MotorInfo>(name, reverse);
}

void Cortex::config(std::string name, SensorPort& sensorPort, SensorPort port) {
	sensorPort = port;
	sensorInfo[port] = std::make_unique<SensorInfo>(name);
}