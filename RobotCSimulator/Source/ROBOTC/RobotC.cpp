#include "RobotC.h"
std::vector<std::unique_ptr<std::thread>> threads;

void startTask(std::function<task()> func) {
	threads.push_back(std::make_unique<std::thread>(func));
}

void delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void config(std::string name, MotorPort& motorPort, MotorPort port, bool reverse) {
	motorPort = port;
	motorReversed[port] = reverse;
	motorName[port] = name;
}