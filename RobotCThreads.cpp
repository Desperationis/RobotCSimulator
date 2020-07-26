#include "RobotC.h"

using namespace RobotC::Types;

std::vector<std::unique_ptr<std::thread>> RobotC::Threads::threads;
bool RobotC::Threads::killAll = false;

void RobotC::Threads::delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void RobotC::Threads::startTask(std::function<task()> func) {
	if (threads.size() < 20) {
		threads.push_back(std::make_unique<std::thread>(func));
	}
	else {
		printf("RobotC.h: The maximum number of tasks (20) has already been reached!");
	}
}

void RobotC::Threads::stopAllTasks() {
	killAll = true;
}