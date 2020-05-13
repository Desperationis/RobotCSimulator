#include "Program.h"
#include "RobotC.h"

MotorPort motor1;

void SetUp() {
	config("motor1", motor1, port1);
}

task PrintTest() {
	while (true) {
		std::cout << motor[port1] << std::endl;

		delay(300);
	}
}

task test() {
	motor[motor1] = 100;
}

task _main() {
	startTask(test);
	startTask(PrintTest);

}