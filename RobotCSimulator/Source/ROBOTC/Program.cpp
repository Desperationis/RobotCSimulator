#include "Program.h"
#include "RobotC.h"

MotorPort motor1;

void SetUp() {
	config("motor1", motor1, port7);
}

task test() {
	motor[motor1] = 69;
	vexRT[Ch3] = 127;
	vexRT[Btn7U] = 1;
}

task programMain() {
	startTask(test);
}