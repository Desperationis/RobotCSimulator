/*****************************************************************//**
 * \file   ProgramRunner.h
 * \brief  Runs a ROBOTC Program.
 *********************************************************************/

#pragma once
#include "Program.h"
#include "../ROBOTCtoC++/RobotC.h"
#include "../ROBOTCtoC++/Cortex.h"

/**
 * Runs the main file of a RobotC Program: Program.h.
 */
class ProgramRunner
{
public:
	ProgramRunner() {
		// Initialize information structs.
		for (int i = 0; i < Cortex::motorInfo.max_size(); i++) {
			Cortex::motorInfo[i] = std::make_unique<MotorInfo>("<none>", false);
		}
		for (int i = 0; i < Cortex::sensorInfo.max_size(); i++) {
			Cortex::sensorInfo[i] = std::make_unique<SensorInfo>("<none>");
		}
	}

	void RunProgram() {
		// Configure Motor and Sensor Values.
		SetUp();

		// Start main function as a thread.
		startTask(programMain);
	}
};

