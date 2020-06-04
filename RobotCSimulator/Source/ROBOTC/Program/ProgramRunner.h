#pragma once
#include "Program.h"
#include "../ROBOTCtoC++/RobotC.h"

/*
 * ProgramRunner.h
 *
 * Runs the main file of a RobotC Program: Program.h.
 */

class ProgramRunner
{
public:
	ProgramRunner() {
		// Initialize information structs.
		for (int i = 0; i < motorInfo.max_size(); i++) {
			motorInfo[i] = std::make_unique<MotorInfo>("<none>", false);
		}
		for (int i = 0; i < sensorInfo.max_size(); i++) {
			sensorInfo[i] = std::make_unique<SensorInfo>("<none>");
		}
	}

	void RunProgram() {
		// Configure Motor and Sensor Values.
		SetUp();

		// Start main function as a thread.
		startTask(programMain);
	}
};

