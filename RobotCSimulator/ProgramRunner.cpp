#include "ProgramRunner.h"
#include "Program.h"
#include "RobotC.h"

void ProgramRunner::RunProgram() {
	SetUp();
	// Start main function as a thread.
	startTask(_main);
}