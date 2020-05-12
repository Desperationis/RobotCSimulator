#include "Program.h"
#include "RobotC.h"

task PrintTest() {
	while (true) {
		std::cout << "test function is called." << std::endl;

		delay(300);
	}
	
}

task _main() {
	startTask(PrintTest);

}