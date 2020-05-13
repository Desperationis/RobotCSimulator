#include "Program.h"
#include "RobotC.h"
std::array<int, 10> motors;

MotorPort motor1;

void SetUp() {
	config("motor1", motor1, port5);
}

task PrintTest() {
	while (true) {
		std::cout << motors[port5] << std::endl;

		delay(300);
	}
}

task test() {
	motors[motor1] = 100;
}

task _main() {
	startTask(test);
	startTask(PrintTest);

}