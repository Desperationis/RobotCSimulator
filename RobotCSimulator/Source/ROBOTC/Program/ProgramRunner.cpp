#include "ProgramRunner.h"
#include "Program.h"
#include "../ROBOTCtoC++/RobotC.h"

ProgramRunner::ProgramRunner() {
	for (int i = 0; i < motorInfo.max_size(); i ++ ) {
		motorInfo[i] = std::make_unique<MotorInfo>("<none>", false);
	}
	for (int i = 0; i < sensorInfo.max_size(); i++) {
		sensorInfo[i] = std::make_unique<SensorInfo>("<none>");
	}
}

void ProgramRunner::RunProgram() {
	SetUp();
	// Start main function as a thread.
	startTask(programMain);
}