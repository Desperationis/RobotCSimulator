#include "ProgramRunner.h"
#include "Program.h"
#include "RobotC.h"

ProgramRunner::ProgramRunner() {
	for (int i = 0; i < 10; i ++ ) {
		motorInfo[i] = std::make_unique<MotorInfo>("<none>", false);
	}
}

void ProgramRunner::RunProgram() {
	SetUp();
	// Start main function as a thread.
	startTask(programMain);
}