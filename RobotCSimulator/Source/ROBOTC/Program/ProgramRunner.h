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
		Cortex::Cortex();
	}

	void RunProgram() {
		// Configure Motor and Sensor Values.
		SetUp();

		// Start main function as a thread.
		startTask(programMain);
	}
};

