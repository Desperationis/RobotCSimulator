#include "RobotC.h"
#include "Cortex.h"

void startTask(std::function<task()> func) {
	Cortex::threads.push_back(std::make_unique<std::thread>(func));
}

void delay(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
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