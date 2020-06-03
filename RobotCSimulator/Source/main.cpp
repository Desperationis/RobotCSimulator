#include <memory>
#include "ROBOTC/Program/ProgramRunner.h"
#include "ROBOTC/ROBOTCtoC++/DefineGlobalOnce.h"
#include "Core.h"

/*
 * main.cpp
 *
 * The main program.
 */
int main()
{
	// Run ROBOTC program
	std::unique_ptr<ProgramRunner> programRunner = std::make_unique<ProgramRunner>();
	programRunner->RunProgram();

	// Create Window
	Core world(sf::VideoMode(1500, 900), "RobotCSimulator", false, 60);

	// Program Loop
	while (world.IsRunning()) {
		world.PollEvents();
		world.Render();
	}

	return 0;
}